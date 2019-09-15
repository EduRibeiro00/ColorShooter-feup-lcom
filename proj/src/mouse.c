#include <lcom/lcf.h>
#include "i8042.h"
#include "mouse.h"
#include "keyboard.h"

int hook_id_mouse = 7; //for subscribing the mouse interrupts
uint8_t packet_byte; //variable that will receive a packet byte from the OUT_BUF
bool mouse_ih_check; //checks if the mouse_ih executed without any problem


int mouse_subscribe_int(uint8_t *bit_no){

  *bit_no = hook_id_mouse;

  if(sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_mouse) != 0){
    printf("An error happened!\n");
    return 1;
  }

  return 0;
}


int mouse_unsubscribe_int(){

  if(sys_irqrmpolicy(&hook_id_mouse) != 0){
    printf("An error happened!\n");
    return 1;
  }

  return 0;

}


void (mouse_ih)(){

    uint32_t stat;

    if(sys_inb(STAT_REG, &stat)!= 0){ //reads status regist

        mouse_ih_check = false;
    }else{

    if(stat & OBF){  //if output buffer is full (available for reading)

      uint32_t temp; //temporary variable

      if(sys_inb(OUT_BUF, &temp) == 0){

            if((stat & (PAR_ERR | TO_ERR)) == 0){

              packet_byte = (uint8_t) temp;  //the current packet byte is passed to packet_byte
              mouse_ih_check = true;
            }else mouse_ih_check = false;

      }else mouse_ih_check = false;
    
    }else mouse_ih_check = false;

    }
}


bool check_if_first_byte(uint8_t byte){

  if(byte & FIRST_BYTE_ID)
    return true;
  else return false;

}

int read_ret_value_mouse(uint8_t *ret){

  uint32_t temp;
  uint32_t stat;
  uint8_t wait_cnt = 0; //counts the amount of times that we had to wait due to the input buffer being full

    while( wait_cnt <= MAX_WAIT ){    //after 5 tries, it gives up

    if(sys_inb(STAT_REG, &stat) != 0)
      return 1;

    if( (stat & OBF) && (stat & AUX) ) {  //if the output buffer is full and bit AUX is set

        if(sys_inb(OUT_BUF, &temp) != 0)
           return 1;
          
        if ( (stat &(PAR_ERR | TO_ERR)) == 0 ){
              
            *ret = (uint8_t) temp;
            return 0;
        }
        else return 1;
    }

    tickdelay(micros_to_ticks(DELAY_US));
    wait_cnt++; //increments the wait counter
    }

return 1; //it needeed to wait to long, which made the function give up

}



int disable_mouse_int(){

  uint8_t cmd_byte;

  if(issue_command(READ_CMD_BYTE) != 0)
    return 1; //if it can't issue the command

  if(read_ret_value(&cmd_byte) != 0)
    return 1; //if it can't get the return value of the command issued

  cmd_byte &= DIS_INT_MOUSE_BYTE; //sets bit 1 to 0

  if(write_command_byte(cmd_byte) != 0) //if it can't write the cmd byte
    return 1;

   return 0;
}


int issue_mouse_cmd(uint8_t mouse_cmd, uint8_t *ackByte){

  if(issue_command(WRITE_BYTE_MOUSE) != 0) //issues the command 0xD4 to the KBC
    return 1;

  if(issue_arg(mouse_cmd) != 0) //issues the mouse command as the arg of command 0xD4
    return 1;

  do{

  if(read_ret_value_mouse(ackByte) != 0) //extracts the acknowledgment byte from the OUT_BUF
    return 1;

  }while(! ((*ackByte == ACK) || (*ackByte == NACK) || (*ackByte == ERROR))); //makes sure that value read from OUT_BUF was indeed the acknowledgment byte of our command

  return 0;
}


int16_t convert2sComp(uint8_t delta, bool sign){

    if (!sign){         //positive number
        return delta;
    }
    else{                   //negative number
        if(delta == 0)
            return -256;
        else
            return -((delta^0xFF)+1);    //2's complement conversion
    }
}


int parse_packet(struct packet *pp){

  if((*pp).bytes[0] & MOUSE_LB) //left button
    (*pp).lb = true;
  else (*pp).lb = false;

  if((*pp).bytes[0] & MOUSE_RB) //right button
    (*pp).rb = true;
  else (*pp).rb = false;

  if((*pp).bytes[0] & MOUSE_MB) //middle button
    (*pp).mb = true;
  else (*pp).mb = false;

  bool x_sign, y_sign;

  if((*pp).bytes[0] & MOUSE_X_SIGN) //x sign
    x_sign = true;
  else x_sign = false;

  if((*pp).bytes[0] & MOUSE_Y_SIGN) //y sign
    y_sign = true;
  else y_sign = false;

  if((*pp).bytes[0] & MOUSE_X_OV) //x overflow
    (*pp).x_ov = true;
  else (*pp).x_ov = false;

  if((*pp).bytes[0] & MOUSE_Y_OV) //y overflow
    (*pp).y_ov = true;
  else (*pp).y_ov = false;

  int16_t deltaX = convert2sComp((*pp).bytes[1], x_sign);
  int16_t deltaY = convert2sComp((*pp).bytes[2], y_sign);

  (*pp).delta_x = deltaX;
  (*pp).delta_y = deltaY;

  return 0;
}


int absValue(int value){

  if(value < 0)
    return -value;
  else return value;

}


void mouse_event_handler(struct mouse_ev event_st, struct state_machine *st, uint8_t x_len, uint8_t tolerance){

    switch(st->currentState){

        case INITIAL:

            if(event_st.type == LB_PRESSED)
              st->currentState = DRAWING_L;

            break;

        
        case DRAWING_L:

            if(event_st.type == MOUSE_MOV){

              if((event_st.delta_x < 0) && (absValue(event_st.delta_x) > tolerance)){ //if there is a negative x displacement of the current packet bigger than the tolerance

              st->x_displacement = 0; //displacements are set to 0
              st->y_displacement = 0; //displacements are set to 0
              st->currentState = INITIAL;

            }else if((event_st.delta_y < 0) && (absValue(event_st.delta_y) > tolerance)){//if there is a negative y displacement of the current packet bigger than the tolerance


              st->x_displacement = 0; //displacements are set to 0
              st->y_displacement = 0; //displacements are set to 0
              st->currentState = INITIAL;

            }else{
                //adds the deltas of the current packet to the x and y displacements
              st->x_displacement += event_st.delta_x;
              st->y_displacement += event_st.delta_y;

            
            }
            }
            else if(event_st.type == LB_RELEASED){

              int x = absValue(st->x_displacement);
              int y = absValue(st->y_displacement);

              if( (x >= x_len) && ( ((double) y / x) > 1)){ //if the line drawn was long enough and had the correct slope

              st->currentState = MIDDLE; //we are now in the middle of both lines (after the end of the first but before the start of the second)
              st->x_displacement = 0; //displacements are set to 0
              st->y_displacement = 0; //displacements are set to 0

            }
            else{
              st->currentState = INITIAL;
              st->x_displacement = 0; //displacements are set to 0
              st->y_displacement = 0; //displacements are set to 0
            }

            }else if(event_st.type == BUTTON_EV){

              st->currentState = INITIAL;
              st->x_displacement = 0; //displacements are set to 0
              st->y_displacement = 0; //displacements are set to 0

            }
            
            break;


        case MIDDLE:

            if(event_st.type == MOUSE_MOV){

              if((absValue(event_st.delta_x) > tolerance) || (absValue(event_st.delta_y) > tolerance)){

              st->currentState = INITIAL; //resets the movement sequence
              st->x_displacement = 0; //displacements are set to 0
              st->y_displacement = 0; //displacements are set to 0

              }


            }else if(event_st.type == LB_PRESSED){

              st->currentState = DRAWING_L; //goes to the drawing state of the first line
              st->x_displacement = 0; //displacements are set to 0
              st->y_displacement = 0; //displacements are set to 0

            }else if(event_st.type == RB_PRESSED){

              st->currentState = DRAWING_R;
            
            }else if(event_st.type == BUTTON_EV){

              st->currentState = INITIAL; //resets the movement sequence
              st->x_displacement = 0; //displacements are set to 0
              st->y_displacement = 0; //displacements are set to 0

            }

            break;


        case DRAWING_R:

          if(event_st.type == RB_RELEASED){

            int x = absValue(st->x_displacement);
            int y = absValue(st->y_displacement);

              if( (x >= x_len) && ( ((double) y / x) > 1)){ //if the line drawn was long enough and had the correct slope

              st->currentState = COMPLETE; //goes to the final state (movement complete!)
              st->x_displacement = 0; //displacements are set to 0
              st->y_displacement = 0; //displacements are set to 0

            }
            else{
              st->currentState = INITIAL;

              st->x_displacement = 0; //displacements are set to 0
              st->y_displacement = 0; //displacements are set to 0
            }


          }else if(event_st.type == MOUSE_MOV){

              if((event_st.delta_x < 0) && (absValue(event_st.delta_x) > tolerance)){ //if there is a negative x displacement of the current packet bigger than the tolerance

              st->x_displacement = 0; //displacements are set to 0
              st->y_displacement = 0; //displacements are set to 0
              st->currentState = INITIAL;

            }else if((event_st.delta_y > 0) && (absValue(event_st.delta_y) > tolerance)){ //if there is a positive y displacement of the current packet bigger than the tolerance


              st->x_displacement = 0; //displacements are set to 0
              st->y_displacement = 0; //displacements are set to 0
              st->currentState = INITIAL;

            }else{

              //adds the deltas of the current packet to the x and y displacements
              st->x_displacement += event_st.delta_x;
              st->y_displacement += event_st.delta_y;

            }
            }else if(event_st.type == BUTTON_EV){

              st->currentState = INITIAL;
              st->x_displacement = 0; //displacements are set to 0
              st->y_displacement = 0; //displacements are set to 0

            }
            
            break;

        case COMPLETE:
            break;

          }

        }



void mouse_event_detect(struct packet *pp, struct mouse_ev *event_st){

    //static lower level state machine (retains its state after multiple calls of the function)
    static ll_state ll_machine = NO_BUT_PRESSED;


     if(ll_machine == NO_BUT_PRESSED){

      //if all the buttons continue to not be pressed
      if((!(pp->lb)) && (! (pp->mb)) && (! (pp->rb))){

        event_st->type = MOUSE_MOV;
        event_st->delta_x = pp->delta_x;
        event_st->delta_y = pp->delta_y;
        return;

      //if the left button was just pressed (while all others released)
      }else if(pp->lb && (! (pp->mb)) && (! (pp->rb))){

        event_st->type = LB_PRESSED;
        ll_machine = LB_PR;
        return;

      //if the right button was just pressed (while all others released)
      }else if(pp->rb && (! (pp->mb)) && (! (pp->lb))){

        event_st->type = RB_PRESSED;
        ll_machine = RB_PR;
        return;

      //other button combinations
      }else {

        ll_machine = OTHER_BUT_COMB;
        event_st->type = BUTTON_EV;
        return;

      }

    }
    else if(ll_machine == LB_PR){

      //if all the buttons are not being pressed (left one was released)
      if((!(pp->lb)) && (! (pp->mb)) && (! (pp->rb))){

        event_st->type = LB_RELEASED;
        ll_machine = NO_BUT_PRESSED;
        return;

      //if the left button continues to be the only one pressed
      }else if(pp->lb && (! (pp->mb)) && (! (pp->rb))){

        event_st->type = MOUSE_MOV;
        event_st->delta_x = pp->delta_x;
        event_st->delta_y = pp->delta_y;
        return;
        
      //other button combinations
      }else{

        ll_machine = OTHER_BUT_COMB;
        event_st->type = BUTTON_EV;
        return;

      }

    }
    else if(ll_machine == RB_PR){

      //if all the buttons are not being pressed (right one was released)
      if((!(pp->lb)) && (! (pp->mb)) && (! (pp->rb))){

        event_st->type = RB_RELEASED;
        ll_machine = NO_BUT_PRESSED;
        return;

      //if the right button continues to be the only one pressed
      }else if((!(pp->lb)) && (! (pp->mb)) &&  pp->rb){

        event_st->type = MOUSE_MOV;
        event_st->delta_x = pp->delta_x;
        event_st->delta_y = pp->delta_y;
        return;
        
      //other button combinations
      }else{

        ll_machine = OTHER_BUT_COMB;
        event_st->type = BUTTON_EV;
        return;

      }


    }
    else if(ll_machine == OTHER_BUT_COMB){

        //if all the buttons are not being pressed (all the buttons that were being pressed were released)
        if((!(pp->lb)) && (! (pp->mb)) && (! (pp->rb))){

            ll_machine = NO_BUT_PRESSED;
            event_st->type = BUTTON_EV;
            return;

        //if only right button is being pressed now
        }else if((!(pp->lb)) && (! (pp->mb)) &&  pp->rb){

            ll_machine = RB_PR;
            event_st->type = BUTTON_EV;
            return;

        //if only left button is being pressed now
        }else if(pp->lb && (! (pp->mb)) && (! (pp->rb))){

            ll_machine = LB_PR;
            event_st->type = BUTTON_EV;
            return;

        
        //if other button combinations continue to be executed
        }else{

          event_st->type = BUTTON_EV;
          return;

        }

    }

}
