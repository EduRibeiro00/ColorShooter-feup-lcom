#include <lcom/lcf.h>
#include "Button.h"
#include "video.h"

struct button_t{
  int x, y; ///< button's leftmost pixel coordinates
  int width, height; ///< width and height of the button images
  char* pixmaps[2]; ///< button pixmaps (1st one is normal pixmap, 2nd one is highlighted pixmap)
  bool cursor_over; ///< true if the cursor is over the button
};


Button* create_button(xpm_string_t normal[], xpm_string_t highlighted[], int x, int y){

  xpm_image_t imgNormal;
  if(xpm_load(normal, XPM_8_8_8, &imgNormal) == BUTTON_ALLOC_FAILED)
    return BUTTON_ALLOC_FAILED;

  xpm_image_t imgHigh;
  if(xpm_load(highlighted, XPM_8_8_8, &imgHigh) == BUTTON_ALLOC_FAILED)
    return BUTTON_ALLOC_FAILED;

  Button* bt = (Button*) malloc(sizeof(Button));
  if(bt == BUTTON_ALLOC_FAILED)
    return BUTTON_ALLOC_FAILED;

  bt->x = x;
  bt->y = y;
  bt->width = imgNormal.width;
  bt->height = imgNormal.height;
  bt->pixmaps[0] = (char*) imgNormal.bytes;
  bt->pixmaps[1] = (char*) imgHigh.bytes;
  
  bt->cursor_over = false;
  
  return bt;
}

//-------------------

void delete_button(Button* bt){

  if(bt == NULL)
    return;

  if(bt->pixmaps[0])
    free(bt->pixmaps[0]);
  
  if(bt->pixmaps[1])
    free(bt->pixmaps[1]);

  free(bt);
  bt = NULL;
}

//-------------------

void highlight_button(Button* bt){
  bt->cursor_over = true;
}

//-------------------

void unhighlight_button(Button* bt){
  bt->cursor_over = false;
}

//-------------------

void draw_button(Button* bt){

  if(bt->cursor_over)
    draw_pixmap_db(bt->pixmaps[1], bt->x, bt->y, bt->width, bt->height);
  else draw_pixmap_db(bt->pixmaps[0], bt->x, bt->y, bt->width, bt->height);
}

//-------------------

int get_bt_x(Button* bt){
  return bt->x;
}

//-------------------

int get_bt_y(Button* bt){
  return bt->y;
}

//-------------------

int get_bt_width(Button* bt){
  return bt->width;
}

//-------------------

int get_bt_height(Button* bt){
  return bt->height;
}
