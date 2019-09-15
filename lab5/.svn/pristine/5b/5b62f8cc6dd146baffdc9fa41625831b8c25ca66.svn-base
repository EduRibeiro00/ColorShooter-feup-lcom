// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <machine/int86.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Any header files included below this line should have been created by you
#include "i8042.h"
#include "keyboard.h"
#include "v_macros.h"
#include "video.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

extern int hook_id_kbd;
extern uint8_t key_code;
extern bool ih_check;
extern uint32_t global_int_counter;
extern int hook_id;




int(video_test_init)(uint16_t mode, uint8_t delay) {

  if (set_graph_mode(mode) != 0)
    return 1;

  sleep(delay);

  if (vg_exit() != 0)
    return 1;

  return 0;
}




int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {

  if (vg_init(mode) == NULL) {

    if (vg_exit() != 0)
      return 1;

    return 1;
  }

  if (vg_draw_rectangle(x, y, width, height, color) != 0) {

    printf("error drawing the rectangle!\n");

    if (vg_exit() != 0)
      return 1;

    return 1;
  }

  int r;
  uint32_t irq_set;
  uint8_t bit_no;

  if (kbd_subscribe_int(&bit_no) != 0) { //subscribing the KBD interrupts
    printf("An error ocurred!\n");
    return 1;
  }

  irq_set = BIT(bit_no);

  int ipc_status;
  message msg;

  while (key_code != ESC_BRK_CODE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {

      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */

            kbc_ih();

            if (!ih_check) { //if there was an error in the interrupt handler
              return 1;
            }
          }
          break;
        default:
          break; /* no other notifications expected: do nothing */
      }
    }
  }

  if (kbd_unsubscribe_int() != 0) { //unsubscribing the KBD interrupts
    printf("An error ocurred!\n");
    return 1;
  }

  if (vg_exit() != 0)
    return 1;

  return 0;
}





int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {

  if (vg_init(mode) == NULL) {

    if (vg_exit() != 0)
      return 1;

    return 1;
  }

  uint16_t recWidth = get_h_res() / no_rectangles;
  uint16_t recHeight = get_v_res() / no_rectangles;

  uint32_t currentColor = first;

  //cycle for each rectangle line (changes y value)
  for (unsigned j = 0; j < no_rectangles; j++) {

    //cycle for each rectangle, in a certain line (changes x value)
    for (unsigned i = 0; i < no_rectangles; i++) {

      //gets new color for the current rectangle
      currentColor = change_color(j, i, no_rectangles, first, step);

      if (vg_draw_rectangle(recWidth * i, recHeight * j, recWidth, recHeight, currentColor) != 0) {
        printf("Error drawing one of the rectangles!\n");

        if (vg_exit() != 0)
          return 1;

        return 1;
      }
    }
  }

  int r;
  uint32_t irq_set;
  uint8_t bit_no;

  if (kbd_subscribe_int(&bit_no) != 0) { //subscribing the KBD interrupts
    printf("An error ocurred!\n");
    return 1;
  }

  irq_set = BIT(bit_no);

  int ipc_status;
  message msg;

  while (key_code != ESC_BRK_CODE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {

      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */

            kbc_ih();

            if (!ih_check) { //if there was an error in the interrupt handler
              return 1;
            }
          }
          break;
        default:
          break; /* no other notifications expected: do nothing */
      }
    }
  }

  if (kbd_unsubscribe_int() != 0) { //unsubscribing the KBD interrupts
    printf("An error ocurred!\n");
    return 1;
  }

  if (vg_exit() != 0)
    return 1;

  return 0;
}






int(video_test_xpm)(const char *xpm[], uint16_t x, uint16_t y) {

  //sets the mode to 0x105
  if (vg_init(MODE_1024x768) == NULL) {

    if (vg_exit() != 0)
      return 1;

    return 1;
  }

  int width, height;

  //reads the xpm and puts width and heights with the correct values
  const char *sprite = read_xpm(xpm, &width, &height);

  if (sprite == NULL) {
    printf("Error in read_xpm!\n");

    if (vg_exit() != 0)
      return 1;

    return 1;
  }

  //draws the xpm
  if (draw_pixmap(sprite, x, y, width, height) != 0) {
    printf("Error drawing the pixmap on the screen!\n");

    if (vg_exit() != 0)
      return 1;

    return 1;
  }

  //Cycle to return minix to text mode if ESC key was pressed
  int r;
  uint32_t irq_set;
  uint8_t bit_no;

  if (kbd_subscribe_int(&bit_no) != 0) { //subscribing the KBD interrupts
    printf("An error ocurred!\n");
    return 1;
  }

  irq_set = BIT(bit_no);

  int ipc_status;
  message msg;

  while (key_code != ESC_BRK_CODE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {

      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */

            kbc_ih();

            if (!ih_check) { //if there was an error in the interrupt handler
              return 1;
            }
          }
          break;
        default:
          break; /* no other notifications expected: do nothing */
      }
    }
  }

  if (kbd_unsubscribe_int() != 0) { //unsubscribing the KBD interrupts
    printf("An error ocurred!\n");
    return 1;
  }

  if (vg_exit() != 0)
    return 1;

  return 0;
}






int(video_test_move)(const char *xpm[], uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf, int16_t speed, uint8_t fr_rate) {

  if (vg_init(MODE_1024x768) == NULL) {

    if (vg_exit() != 0)
      return 1;

    return 1;
  }

  int r;
  uint32_t irq_set_timer0;
  uint32_t irq_set_kbd;
  uint8_t bit_no_timer;
  uint8_t bit_no_keyboard;
  int nr_frames_passed = 0;

  if (kbd_subscribe_int(&bit_no_keyboard) != 0) { //subscribing the KBD interrupts
    printf("An error ocurred!\n");
    return 1;
  }
  if (timer_subscribe_int(&bit_no_timer) != 0) { //subscribing the timer interrupts
    printf("An error ocurred!\n");
    return 1;
  }

  irq_set_kbd = BIT(bit_no_keyboard);
  irq_set_timer0 = BIT(bit_no_timer);

  int width, height;

  const char *sprite = read_xpm(xpm, &width, &height);

  if (sprite == NULL)
    return 1;

  uint8_t time_for_frame = sys_hz() / fr_rate;

  //draws first image (frame 0)
  if (draw_pixmap(sprite, xi, yi, width, height) != 0)
    return 1;


  int distance_left;


    if(xi == xf)
      distance_left = abs(yf-yi);
    else distance_left = abs(xf-xi);


  int ipc_status;
  message msg;

  while (key_code != ESC_BRK_CODE) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {

      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:

          if (msg.m_notify.interrupts & irq_set_kbd) { /* subscribed interrupt */

            kbc_ih();

            if (!ih_check) { //if there was an error in the interrupt handler
              return 1;
            }
          }

          if (msg.m_notify.interrupts & irq_set_timer0) { /* subscribed timer interrupt */

           timer_int_handler(); //increments the global counter upon an interrupt

            //------------------
            //if speed is positive
            //------------------
            if(speed > 0){

            if ((global_int_counter % time_for_frame == 0) && (distance_left > 0)) {
          
                //final image was already drawn; no need to keep updating the sprite
                if((xi == xf) && (yi == yf))
                  continue;

                //movement is in y
                if(xi == xf){

                  if(yf > yi)
                    yi += speed;
                  else yi -= speed;

                  distance_left -= speed;

                  //if we would go past the final point, put the coordinates in the final point
                  if(distance_left < 0)
                    yi = yf;
                  
                  clear_screen();
                  if (draw_pixmap(sprite, xi, yi, width, height) != 0)
                    return 1;
                }
                //movement is in x
                else{

                    if(xf > xi)
                      xi += speed;
                    else xi -= speed;

                    distance_left -= speed;

                    //if we would go past the final point, put the coordinates in the final point
                    if(distance_left < 0)
                      xi = xf;

                    clear_screen();
                    if (draw_pixmap(sprite, xi, yi, width, height) != 0)
                      return 1;

                }

            }
            }
            //------------------
            //if speed is negative
            //------------------
            else{

              if (global_int_counter % time_for_frame == 0)
                nr_frames_passed++;

              if ((nr_frames_passed == abs(speed)) && (distance_left > 0)){
                nr_frames_passed = 0; //reset value

                //final image was already drawn; no need to keep updating the sprite
                if((xi == xf) && (yi == yf))
                  continue;

                //movement is in y
                if(xi == xf){

                  if(yf > yi)
                    yi += 1;
                  else yi -= 1;

                  distance_left -= 1;
                  
                  clear_screen();
                  if (draw_pixmap(sprite, xi, yi, width, height) != 0)
                    return 1;
                }
                //movement is in x
                else{

                    if(xf > xi)
                      xi += 1;
                    else xi -= 1;

                    distance_left -= 1;

                    clear_screen();
                    if (draw_pixmap(sprite, xi, yi, width, height) != 0)
                      return 1;

                }

              }
            }
            }

            break;
            default:
              break; /* no other notifications expected: do nothing */
          }
      }  
    
    }

    if (kbd_unsubscribe_int() != 0) { //unsubscribing the KBD interrupts
      printf("An error ocurred!\n");
      return 1;
    }

    if(timer_unsubscribe_int() != 0){ //unsubscribing the timer interrupts
      printf("An error ocurred!\n");
      return 1;
    }

    if (vg_exit() != 0)
      return 1;

    return 0;
  }





  int(video_test_controller)() {

    vg_vbe_contr_info_t ctrl_info;
    vbe_info_block_t info_block;

    if (vbe_get_ctrl_info(&ctrl_info, &info_block) != 0){
      printf("Error in the 0x4F00 function call!\n"); 
      return 1;
    }

    if (vg_display_vbe_contr_info(&ctrl_info) != 0) {
      printf("Couldn't print out the information!\n");
      return 1;
    }

    return 0;
  }
