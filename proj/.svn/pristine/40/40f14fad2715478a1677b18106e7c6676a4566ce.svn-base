// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <machine/int86.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <minix/sysutil.h>

// Any header files included below this line should have been created by you
#include "video.h"
#include "v_macros.h"
#include "Game.h"


int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (proj_main_loop)(int UNUSED(argc), char *UNUSED(argv[])) {

  sys_enable_iop(SELF); //to enable assembly IO operations


  if (vg_init(MODE_800x600) == NULL) {

    if(vg_exit() != 0)
      return 1;

    return 1;
  }
  
  srand(time(NULL));


  Game* g = start_game();
  play_game(g);
  end_game(g);


  if(vg_exit() != 0)
    return 1;

    return 0;
}
