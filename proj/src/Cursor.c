#include <lcom/lcf.h>
#include <stdio.h>
#include <stdlib.h>
#include "Cursor.h"
#include "mouse.h"
#include "video.h"
#include "i8042.h"

struct cursor_t{

int x_pos;  ///< current x position
int y_pos;  ///< current y position
int width; ///< width of the cursor image
int height; ///< height of the cursor image
bool lb_status; ///< if the left button is pressed or not
char* pixmap; ///< pixmap of the cursor image
};

//-------------------

Cursor* create_cursor(xpm_string_t cursor[], int x, int y){

  xpm_image_t img;
  if(xpm_load(cursor, XPM_8_8_8, &img) == CURSOR_ALLOC_FAILED)
    return CURSOR_ALLOC_FAILED;

  Cursor* csr = (Cursor*) malloc(sizeof(Cursor));
  if(csr == CURSOR_ALLOC_FAILED)
    return CURSOR_ALLOC_FAILED;

  csr->x_pos = x;
  csr->y_pos = y;
  csr->lb_status = false; //starts off with the left button unpressed
  csr->pixmap = (char*) img.bytes;
  csr->width = img.width;
  csr->height = img.height;

  return csr;
}

//-------------------

void delete_cursor(Cursor* csr){
  
  if(csr == NULL)
    return;

  if(csr->pixmap)
    free(csr->pixmap);
    
    free(csr);
    csr = NULL;
}

//-------------------

int drawCursor(Cursor* csr){

  return draw_pixmap_db(csr->pixmap, csr->x_pos, csr->y_pos, csr->width, csr->height);
}

//-------------------

int updateCursor(Cursor* csr, struct packet pp){

  if(pp.lb){
    csr->lb_status = true;
  }else csr->lb_status = false;

  csr->x_pos += pp.delta_x;
  csr->y_pos -= pp.delta_y; //in graphical mode, the y coord increases downwards

  if(csr->x_pos < 0)
    csr->x_pos = 0;

  if((unsigned) csr->x_pos >= get_h_res())
    csr->x_pos = get_h_res() - 1;

  if(csr->y_pos < 0)
    csr->y_pos = 0;

  if((unsigned) csr->y_pos >= get_v_res())
    csr->y_pos = get_v_res() - 1;

  return 0;
}

//-------------------

int get_cursor_x(Cursor* csr){
  return csr->x_pos;
}

//-------------------

int get_cursor_y(Cursor* csr){
  return csr->y_pos;
}

//-------------------

bool get_lb_status(Cursor* csr){
  return csr->lb_status;
}
