#include <lcom/lcf.h>
#include "Explosion.h"
#include "video.h"
#include "projMacros.h"

struct explosion_t{

  char* pixmaps[10]; ///< pixmaps of all explosion images
  int currentPixmap; ///< index showing the pixmap currently active
  int x; ///< x coordinate of the top leftmost pixel
  int y; ///< y coordinate of the top leftmost pixel
  int width; ///< width of the explosion 
  int height; ///< height of the explosion
};


Explosion* create_explosion(xpm_image_t explosions[], int arraySize, int x, int y){

    Explosion* exp = (Explosion*) malloc(sizeof(Explosion));
    if(exp == EXPLOSION_ALLOC_FAILED)
      return EXPLOSION_ALLOC_FAILED;

    for(int i = 0; i < arraySize; i++)
      exp->pixmaps[i] = (char *) explosions[i].bytes;

    exp->x = x;
    exp->y = y;
    
    //note: all pixmaps have the same width and height
    exp->width = explosions[0].width;
    exp->height = explosions[0].height;

    exp->currentPixmap = 0;

    return exp;
}

//-------------------

void delete_explosion(Explosion* exp){

  if(exp == NULL)
    return;

  free(exp);
  exp = NULL;
}

//-------------------

bool animate_explosion(Explosion* exp){

  exp->currentPixmap++;

  if(exp->currentPixmap >= 10)
    return true;
  else return false;
}

//-------------------

void draw_explosion(Explosion* exp){

  draw_pixmap_db(exp->pixmaps[exp->currentPixmap], exp->x, exp->y, exp->width, exp->height);
}
