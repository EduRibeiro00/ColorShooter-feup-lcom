#include <lcom/lcf.h>
#include "i8042.h"

  #ifdef LAB3
  int sys_inb_cnt(port_t port, uint32_t *byte);
  #else
  #define sys_inb_cnt(p,q) sys_inb(p,q)
  #endif



int hook_id_kbd = 5; //for subscribing KBD interruputs
uint32_t sys_inb_counter = 0;  //global counter for sys_inb_calls
uint8_t key_code; //variable that will receive the make code or break code from the output buffer
bool ih_check; //checks if the ih executed without any problem



int (kbd_subscribe_int)(uint8_t *bit_no){

  *bit_no = hook_id_kbd;

  if(sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_kbd) != 0){
    printf("An error happened!\n");
    return 1;
  }

  return 0;
}



int (kbd_unsubscribe_int)(){

  if(sys_irqrmpolicy(&hook_id_kbd) != 0){
    printf("An error happened!\n");
    return 1;
  }

  return 0;
}

#ifdef LAB3
int sys_inb_cnt(port_t port, uint32_t *byte){

    if(sys_inb(port, byte) != 0){
      return 1;
    }
    else{
      sys_inb_counter++;  //increments counter
      return 0;
    }

}
#endif

void (kbc_ih)(){

    uint32_t stat;

    if(sys_inb_cnt(STAT_REG, &stat)!= 0){ //reads status regist

        ih_check = false;
    }else{

    if(stat & OBF){   //if output buffer is full (available for reading)

      uint32_t temp; //temporary variable

      if(sys_inb_cnt(OUT_BUF, &temp) == 0){

            if((stat & (PAR_ERR | TO_ERR)) == 0){

              key_code = (uint8_t) temp;  //the current scancode is passed to key_code
              ih_check = true;
            }else ih_check = false;

      }else ih_check = false;
    
    }else ih_check = false;

    }
}

int is_make(uint8_t code, bool *make){

    if(code & BIT(7)){
      *make = false;   //if MSB is set, it is a break code
    }else *make = true;  //otherwise, it is a make code

  return 0;
}


int process_scancode(uint8_t bytes[], uint8_t *size, bool *make, bool *oneByte){

    if(*oneByte){  //the current scancode only has one byte

      *size = 1; //sets the size of the array to one

      bytes[0] = key_code;  //puts the current scancode in the array

      is_make(key_code, make);

      

    }else{  //the current scancode has two bytes

      *size = 2;

      bytes[0] = TWO_BYTE_ID; //first element of the array is 0xe0
      bytes[1] = key_code;  //seconde element is the rest of the scancode

      is_make(key_code, make);

      *oneByte = true; //sets oneByte to true, for the next loop iteration

    }
    
    return 0;
}


int issue_command(uint8_t cmd){

    uint32_t stat;
    uint8_t wait_cnt = 0; //counts the amount of times that we had to wait due to the input buffer being full

    while( wait_cnt <= MAX_WAIT ) { //after 5 tries, it gives up

          if(sys_inb_cnt(STAT_REG, &stat) != 0)
            return 1;
 
          if( (stat & (IBF | AUX)) == 0 ) { //if the input buffer is not full and the AUX bit is not set

          if ( (stat & (PAR_ERR | TO_ERR)) == 0 ){  

          if(sys_outb(IN_BUF_CMD, cmd) != 0)
            return 1;
          
          return 0;
          }
          else return 1;
    }
    tickdelay(micros_to_ticks(DELAY_US));
    wait_cnt++; //increments the wait counter
}

return 1; //it needeed to wait to long, which made the function give up
}


int read_ret_value(uint8_t *ret){

  uint32_t temp;
  uint32_t stat;

      if(sys_inb_cnt(STAT_REG, &stat) != 0)
        return 1;

        if( (stat & OBF) && ((stat & AUX) == 0)) {  //if the output buffer is full and bit AUX is not set

          if(sys_inb_cnt(OUT_BUF, &temp) != 0)
            return 1;
          
          if ( (stat &(PAR_ERR | TO_ERR)) == 0 ){
              
              *ret = (uint8_t) temp;
              return 0;
          }
          else return 1;
    }

return 1;

}


int issue_arg(uint8_t cmd){

    uint32_t stat;

          if(sys_inb_cnt(STAT_REG, &stat) != 0)
            return 1;
 
          if( (stat & (IBF | AUX)) == 0 ) {

          if ( (stat & (PAR_ERR | TO_ERR)) == 0 ){ 

          if(sys_outb(IN_BUF_ARGS, cmd) != 0)
            return 1;
          
          return 0;
          }
       }

return 1;
}


int read_command_byte(uint8_t *cmd_byte){

    if(issue_command(READ_CMD_BYTE) != 0)
      return 1; //if it can't issue the command

    if(read_ret_value(cmd_byte) != 0)
      return 1; //if it can't get the return value of the command issued

    return 0;
}


int write_command_byte(uint8_t cmd_byte){

  if(issue_command(WRITE_CMD_BYTE) != 0)
    return 1; //if it can't issue the command

  if(issue_arg(cmd_byte) != 0)
    return 1; //if it can't send the command

  return 0;
}


int keyboard_enable(){

    uint8_t cmd_byte;

    if(read_command_byte(&cmd_byte) != 0) //if it can't read the cmd byte
      return 1;

    cmd_byte |= KBD_ENABLE_BIT; //to enable interrupts

    if(write_command_byte(cmd_byte) != 0) //if it can't write the cmd byte
      return 1;

    return 0;
}
