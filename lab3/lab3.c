#include <lcom/lcf.h>
#include "keyboard.h"
#include <stdbool.h>
#include <stdint.h>
#include <minix/sysutil.h>
#include "i8042.h"
#include "i8254.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

extern uint32_t global_int_counter;  
extern int hook_id; //hook_id for the timer 
extern int hook_id_keyboard;  //hook_id for the kbd
extern uint32_t sys_inb_counter;
extern uint8_t key_code;
extern bool ih_check;

/* When you use argument assembly for the first time, delete the UNUSED macro */

int (kbd_test_scan)(bool assembly) {

  int r;
  uint32_t irq_set;
  uint8_t bit_no;

  if(kbd_subscribe_int(&bit_no) != 0){  //subscribing the KBD interrupts
    printf("An error ocurred!\n");
    return 1;
  }

  irq_set = BIT(bit_no);

  int ipc_status;
	message msg;
  bool make; //true if the current scancode is a make code; false if it is a break code
  bool oneByte = true; //true if the current scancodes has one byte
  uint8_t size; //size of the bytes array in each loop iteration
  uint8_t bytes[2]; //bytes that are going to be printed in each loop iteration (max length for scancodes is 2 bytes, for this lab)
	
  while(key_code != ESC_BRK_CODE ) { 

	if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
	   printf("driver_receive failed with: %d", r);
	   continue;
	}
	if (is_ipc_notify(ipc_status)) {

	   switch (_ENDPOINT_P(msg.m_source)) {
	       case HARDWARE: 

	           if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
	               
                 if(assembly){
                  kbc_asm_ih(); //calls the interrupt handler in assembly
                 
                 }else kbc_ih(); //calls interrupt handler in C

                  if(!ih_check){ //if there was an error in the interrupt handler
                    return 1;
                  }
                  if(key_code == TWO_BYTE_ID){ //if scancode read is 0xe0
                      oneByte = false;
                      
                      }
                  else{ //if scancode read is a "normal" 1 byte scancode
    
                      process_scancode(bytes, &size, &make, &oneByte);

                      if(kbd_print_scancode(make, size, bytes) != 0){
                          printf("An error ocurred!\n");
                          return 1;
                           }
                           

                  }
             }
	           break;
	       default:
	           break; /* no other notifications expected: do nothing */	
	   }
	}
	}


  if(kbd_unsubscribe_int() != 0){  //unsubscribing the KBD interrupts
    printf("An error ocurred!\n");
    return 1;
  }

  if(!assembly){
    
    if(kbd_print_no_sysinb(sys_inb_counter) != 0){  //prints number of sys_inb calls
    
    return 1;
    }

  }

    return 0;
}




int (kbd_test_poll)(){

  bool make;  //true if the current scancode is a make code; false if it is a break code
  bool oneByte = true; //true if the current scancodes has one byte
  uint8_t size;  //size of the bytes array in each loop iteration
  uint8_t bytes[2];  //bytes that are going to be printed in each loop iteration (max length for scancodes is 2 bytes, for this lab) 

  while (key_code != ESC_BRK_CODE) {
    
    kbc_ih();
    
    if (ih_check) { //new scancode sent
      
      if (key_code == TWO_BYTE_ID) { // if scancode read is 0xe0
        
        oneByte = false;
      }
      else { // if scancode read is a "normal" 1 byte scancode
        
        process_scancode(bytes, &size, &make, &oneByte);
        
        if (kbd_print_scancode(make, size, bytes) != 0) {
          
          printf("An error ocurred!\n");
          return 1;
        }

      }
    
    }
  }

  if (keyboard_enable() != 0) {   //after the loop, it enables interrupts again
    printf("An error ocurred!\n");
    return 1;
  }

   if(kbd_print_no_sysinb(sys_inb_counter) != 0){  //prints number of sys_inb calls

      return 1;
}

  return  0;
}

int (kbd_test_timed_scan)(uint8_t n) {

  int r;
  uint32_t irq_set_timer0;
  uint32_t irq_set_kbd;
  uint8_t bit_no_timer;
  uint8_t bit_no_keyboard;

  if(kbd_subscribe_int(&bit_no_keyboard) != 0){  //subscribing the KBD interrupts
    printf("An error ocurred!\n");
    return 1;
  }
  if(timer_subscribe_int(&bit_no_timer) != 0){   //subscribing the timer interrupts
    printf("An error ocurred!\n");
    return 1;
  }

  irq_set_kbd = BIT(bit_no_keyboard);
  irq_set_timer0 = BIT(bit_no_timer);


  int ipc_status;
	message msg;
  bool make; //true if the current scancode is a make code; false if it is a break code
  bool oneByte = true; //true if the current scancodes has one byte
  uint8_t size; //size of the bytes array in each loop iteration
  uint8_t bytes[2]; //bytes that are going to be printed in each loop iteration (max length for scancodes is 2 bytes, for this lab)


while((key_code != ESC_BRK_CODE) && (global_int_counter < n * sys_hz())) {  //ends the cycle when it reads the 'ESC' key breakcode, or when it goes n seconds without receiving a scancode

	if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
	   printf("driver_receive failed with: %d", r);
	   continue;
	}
	if (is_ipc_notify(ipc_status)) {

switch (_ENDPOINT_P(msg.m_source)) {
  case HARDWARE:
    
    if (msg.m_notify.interrupts & irq_set_timer0) { /* subscribed timer interrupt */

    timer_int_handler(); //increments the global counter upon an interrupt
    }

    if (msg.m_notify.interrupts & irq_set_kbd) { /* subscribed keyboard interrupt */

      kbc_ih(); //calls interrupt handler
                          
          if(!ih_check){ //if there was an error in the interrupt handler
            return 1;
          }
          if(key_code == TWO_BYTE_ID){ //if scancode read is 0xe0
                oneByte = false;
                      
              }
              else{ //if scancode read is a "normal" 1 byte scancode
    
                process_scancode(bytes, &size, &make, &oneByte);

                if(kbd_print_scancode(make, size, bytes) != 0){
                    printf("An error ocurred!\n");
                    return 1;
                    }
                           
                 global_int_counter = 0; //when it prints a scancode, it resets the timer counter to its initial value, 0 

                }
    }
    break;
    
    default:
      break;
    }
  }
}

  if(timer_unsubscribe_int() != 0){ //unsubscribes timer interrupts
    printf("An error ocurred!\n");
    return 1;
  }

  if(kbd_unsubscribe_int() != 0){  //unsubscribing the KBD interrupts
    printf("An error ocurred!\n");
    return 1;
  }

return 0;

}
