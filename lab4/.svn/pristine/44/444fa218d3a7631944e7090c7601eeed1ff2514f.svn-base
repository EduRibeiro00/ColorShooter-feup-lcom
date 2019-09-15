// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "i8042.h"
#include "i8254.h"
#include "keyboard.h"
#include "mouse.h"


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

extern int hook_id_mouse;  //for subscribing the mouse interrupts
extern uint8_t key_code; //variable that will receive the make code or break code from the OUT_BUF
extern uint8_t packet_byte; //variable that will receive a packet byte from the OUT_BUF
extern bool ih_check; //checks if the kbc_ih executed without any problem
extern bool mouse_ih_check; //checks if the mouse_ih executed without any problem
extern unsigned global_int_counter; //global counter for time

int (mouse_test_packet)(uint32_t cnt) {
    
  int r;
  uint32_t irq_set;
  uint8_t bit_no;

  int ipc_status;
	message msg;
  uint32_t printCounter = 0; //counter to keep track of the number of packets printed
  uint8_t ackByte; //byte used to check the acknowledgment byte
  unsigned int currentByte = 0; //used to keep track of the current byte of the data packet
  struct packet pp; //struct that will have all the information about the data packets
	
  if(mouse_subscribe_int(&bit_no) != 0){  //subscribing the mouse interrupts
    printf("An error ocurred!\n");
    return 1;
  }

  irq_set = BIT(bit_no);

  if(sys_irqdisable(&hook_id_mouse) != 0)
    return 1;


  do{
      if( issue_mouse_cmd(ENB_DATA_REP, &ackByte) != 0) //enables data reporting
          return 1;

        if(ackByte == ERROR) //acknowledgment byte was ERROR; terminates program
          return 1;
      
  }while(ackByte != ACK);


  if(sys_irqenable(&hook_id_mouse) != 0)
    return 1;


  while( printCounter < cnt ) { 

	if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
	   printf("driver_receive failed with: %d", r);
	   continue;
	}
	if (is_ipc_notify(ipc_status)) {

	   switch (_ENDPOINT_P(msg.m_source)) {
	       case HARDWARE: 

	          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
	               
                mouse_ih();

                if(!mouse_ih_check)
                  return 1;

                if( (currentByte == 0) && (!check_if_first_byte(packet_byte)) ){ //if the first byte does not have bit 3 set
                  continue;
                }

                pp.bytes[currentByte] = packet_byte;
                
                if(currentByte == 2)
                  currentByte = 0;
                else currentByte++;

                if(currentByte == 0){ //packet is complete
                  
                  parse_packet(&pp);

                  mouse_print_packet(&pp);
                  printCounter++;
                  
                }
              
           }
	         break;
	     default:
	         break; /* no other notifications expected: do nothing */	
	   }
	  }
	}


  if(sys_irqdisable(&hook_id_mouse) != 0)
    return 1;

  do{
      if( issue_mouse_cmd(DIS_DATA_REP, &ackByte) != 0) //disables data reporting
          return 1;

        if(ackByte == ERROR) //acknowledgment byte was ERROR; terminates program
          return 1;
      
  }while(ackByte != ACK);


   if(sys_irqenable(&hook_id_mouse) != 0)
    return 1;


  if(mouse_unsubscribe_int() != 0){  //unsubscribing the mouse interrupts
    printf("An error ocurred!\n");
    return 1;
  }

  return 0;

}


//------------------------------------



int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
     struct packet pp; //struct that will have the information of the packets
    uint8_t counter = 0; //counts the number of polls
    //uint8_t bit_no_mouse;
    uint8_t ackByte;  //byte used to check the acknowledgment byte
 

   while(counter < cnt){

    do{
      if(issue_mouse_cmd(READ_DATA, &ackByte) != 0) //Sends Read data command for the mouse to send the packet data
        return 1;

      if(ackByte == ERROR) //acknowledgment byte was ERROR; terminates program
        return 1;
      
     }while(ackByte != ACK);


      for(unsigned i = 0; i < 3; i++){

      //Sends Read data command for the mouse to send the packet data
      mouse_ih();  
  
      if(!mouse_ih_check)
        return 1;

      pp.bytes[i] = packet_byte;


      }

      parse_packet(&pp);
      mouse_print_packet(&pp);
      counter++;

      tickdelay(micros_to_ticks(period*1000));
  }

   //sets streaming mode
   do{
       if(issue_mouse_cmd(SET_STRM_MODE, &ackByte) != 0)
          return 1;

       if(ackByte == ERROR) //acknowledgment byte was ERROR; terminates program
          return 1;
      
    }while(ackByte != ACK);


 //disables data reporting 
    do{
       if(issue_mouse_cmd(DIS_DATA_REP, &ackByte) != 0) //disables data reporting
          return 1;

       if(ackByte == ERROR) //acknowledgment byte was ERROR; terminates program
          return 1;
      
    }while(ackByte != ACK);


    //Resets the KBC command byte to Minix's default value
    if(write_command_byte(minix_get_dflt_kbc_cmd_byte()) != 0)
      return 1;
   
    
  return 0;
}


//--------------------------------


int (mouse_test_async)(uint8_t idle_time) {

   uint8_t ackByte; //byte used to check the acknowledgment byte
  unsigned int currentByte = 0; //used to keep track of the current byte of the data packet
  struct packet pp; //struct that will have all the information about the data packets
    
  //Stores bit mask in irq_mouse and irq_timer and subscribes interrupts for both devices
  uint32_t irq_set_mouse, irq_set_time;
  uint8_t bit_no_mouse, bit_no_timer;

  if(timer_subscribe_int(&bit_no_timer) != 0)
    return 1;
  
  irq_set_time = BIT(bit_no_timer);


  if(mouse_subscribe_int(&bit_no_mouse) != 0)
    return 1;
  
  irq_set_mouse = BIT(bit_no_mouse);


  if(sys_irqdisable(&hook_id_mouse) != 0)
    return 1;

  do{
      if( issue_mouse_cmd(ENB_DATA_REP, &ackByte) != 0) //enables data reporting
          return 1;

        if(ackByte == ERROR) //acknowledgment byte was ERROR; terminates program
          return 1;
      
  }while(ackByte != ACK);


  if(sys_irqenable(&hook_id_mouse) != 0)
    return 1;


  int ipc_status, r;
  message msg;

  // Checks if it has not received inputs for idle_time seconds to end the loop
  while(global_int_counter < idle_time * sys_hz()) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
      printf("driver_receive failed with: %d", r);
      continue;
    }


    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
      case HARDWARE:

            if(msg.m_notify.interrupts & irq_set_time){
        timer_int_handler(); //increments the global counter upon an interrupt
    }


        if (msg.m_notify.interrupts & irq_set_mouse){ //Calls interrupt handler and prints packets

                 mouse_ih();

                if(!mouse_ih_check)
                  return 1;

                if( (currentByte == 0) && (!check_if_first_byte(packet_byte)) ){ //if the first byte does not have bit 3 set
                  continue;
                }

                pp.bytes[currentByte] = packet_byte;
                
                if(currentByte == 2)
                  currentByte = 0;
                else currentByte++;

                if(currentByte == 0){ //packet is complete
                  
                  parse_packet(&pp);

                  mouse_print_packet(&pp);

                  global_int_counter = 0; //if it prints a packet, resets timer
                }
        }

        break;
      default:
        break;
      }
    }
    
  }

  
  if(sys_irqdisable(&hook_id_mouse) != 0)
    return 1;

  do{
      if( issue_mouse_cmd(DIS_DATA_REP, &ackByte) != 0) //disables data reporting
          return 1;

        if(ackByte == ERROR) //acknowledgment byte was ERROR; terminates program
          return 1;
      
  }while(ackByte != ACK);

  if(sys_irqenable(&hook_id_mouse) != 0)
    return 1;


  //Unsubscribes the interruptions on both mouse and timer
  if(timer_unsubscribe_int()!=0)
    return -1;

  if(mouse_unsubscribe_int()!=0)
    return -1;

  return 0;

}



//---------------------------


int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {

  int r;
  uint32_t irq_set;
  uint8_t bit_no;

  int ipc_status;
	message msg;
  uint8_t ackByte; //byte used to check the acknowledgment byte
  unsigned int currentByte = 0; //used to keep track of the current byte of the data packet
  struct packet pp; //struct that will have all the information about the data packets
  struct state_machine st; //state machine
	struct mouse_ev event_st; //event structure

  if(mouse_subscribe_int(&bit_no) != 0){  //subscribing the mouse interrupts
    printf("An error ocurred!\n");
    return 1;
  }

  irq_set = BIT(bit_no);


  if(sys_irqdisable(&hook_id_mouse) != 0)
    return 1;


  do{
      if( issue_mouse_cmd(ENB_DATA_REP, &ackByte) != 0) //enables data reporting
          return 1;

        if(ackByte == ERROR) //acknowledgment byte was ERROR; terminates program
          return 1;
      
  }while(ackByte != ACK);


  if(sys_irqenable(&hook_id_mouse) != 0)
    return 1;


  st.currentState = INITIAL;

  while(st.currentState != COMPLETE) { 

	if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
	   printf("driver_receive failed with: %d", r);
	   continue;
	}
	if (is_ipc_notify(ipc_status)) {

	   switch (_ENDPOINT_P(msg.m_source)) {
	       case HARDWARE: 

	          if (msg.m_notify.interrupts & irq_set) { // subscribed interrupt 
	               
                mouse_ih();

                if(!mouse_ih_check)
                  return 1;

                if( (currentByte == 0) && (!check_if_first_byte(packet_byte)) ){ //if the first byte does not have bit 3 set
                  continue;
                }

                pp.bytes[currentByte] = packet_byte;
                
                if(currentByte == 2)
                  currentByte = 0;
                else currentByte++;

                if(currentByte == 0){ //packet is complete
                  
                  parse_packet(&pp); //parses the packet

                  mouse_print_packet(&pp);

                  mouse_event_detect(&pp, &event_st); //detects the current event

                  mouse_event_handler(event_st, &st, x_len, tolerance); //handles the event accordingly

                }
              
           }
	         break;
	     default:
	         break; // no other notifications expected: do nothing 	
	   }
	  }else{ // received standard message, not notification 

    }
	}


  if(sys_irqdisable(&hook_id_mouse) != 0)
    return 1;

  do{
      if( issue_mouse_cmd(DIS_DATA_REP, &ackByte) != 0) //disables data reporting
          return 1;

        if(ackByte == ERROR) //acknowledgment byte was ERROR; terminates program
          return 1;
      
  }while(ackByte != ACK);


   if(sys_irqenable(&hook_id_mouse) != 0)
    return 1;


  if(mouse_unsubscribe_int() != 0){  //unsubscribing the mouse interrupts
    printf("An error ocurred!\n");
    return 1;
  }

  return 0;
  
}
