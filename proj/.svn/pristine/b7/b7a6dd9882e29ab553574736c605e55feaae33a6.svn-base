#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <machine/int86.h>
#include "video.h"
#include "v_macros.h"

static void *video_mem;		/* Process (virtual) address to which VRAM is mapped */
static void *double_buffer; /* double buffer */

static unsigned h_res;	        /* Horizontal resolution in pixels */
static unsigned v_res;	        /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */
static unsigned color_mode;     /* Value of the color mode */
static unsigned bytes_per_pixel; /* Number of bytes a pixel ocuppies, in a certain video mode */

int r;
struct minix_mem_range mr;
static unsigned int vram_base;  /* VRAM's physical addresss */
static unsigned int vram_size;  /* VRAM's size, but you can use the frame-buffer size, instead */

static unsigned RedMaskSize;
static unsigned RedFieldPosition;
static unsigned GreenMaskSize;
static unsigned GreenFieldPosition;
static unsigned BlueMaskSize;
static unsigned BlueFieldPosition;

unsigned get_color_mode(){
  return color_mode;
}


unsigned get_h_res(){
  return h_res;
}


unsigned get_v_res(){
  return v_res;
}


unsigned get_bitspp(){
  return bits_per_pixel;
}

unsigned get_bytespp(){
  return bytes_per_pixel;
}

struct minix_mem_range get_minix_memory_range(){
  return mr;
}


unsigned int get_vram_base(){
  return vram_base;
}


unsigned int get_vram_size(){
  return vram_size;
}

void* get_video_mem(){
  return video_mem;
}

void* get_db(){
  return double_buffer;
}

void DBtoVM(){
  memcpy(video_mem, double_buffer, vram_size);
}


int vbe_get_info_about_mode(uint16_t mode, vbe_mode_info_t *vmi_p){

  if(lm_init(false) == NULL){
    printf("lm_init failed!\n");
    return 1;
  }

  phys_bytes buf;
  mmap_t map;
  struct reg86u reg86;

  memset(&reg86, 0, sizeof(reg86)); //clears the structure

  unsigned num_tries = 0;

  //tries to use lm_alloc(); if it fails a max number of times, terminates the program
  while(num_tries < ALLOC_MAX_TRIES){

    if(lm_alloc(sizeof(vbe_mode_info_t), &map) == NULL)
      num_tries++;
    else{
      num_tries = 0;
      break;
    }
  }

  if(num_tries == ALLOC_MAX_TRIES){
    printf("lm_alloc failed!\n");
    return 1;
  }

  buf = map.phys;

  reg86.u.b.intno = VID_CARD_I_VEC;
  reg86.u.w.ax = RET_VBE_MODE; //0x4F01
  reg86.u.w.es = PB2BASE(buf);
  reg86.u.w.di = PB2OFF(buf);
  reg86.u.w.cx = mode;

  if( sys_int86(&reg86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }

  //ah register is set to 0 if everything was sucessful
  if(reg86.u.b.ah != 0)
    return 1;

  //the struct variable now has all the information needed
  *vmi_p = *((vbe_mode_info_t*) map.virt);

  if(!lm_free(&map)){
    printf("lm_free failed!\n");
    return 1;
  }
  
  return 0;
}


int set_graph_mode(uint16_t mode){

  struct reg86u reg86;

  memset(&reg86, 0, sizeof(reg86)); //clears the structure

  reg86.u.b.intno = VID_CARD_I_VEC;
  reg86.u.w.ax = SET_VBE_MODE; //0x4F02
  reg86.u.w.bx = SET_LINEAR_FB | mode;


  if( sys_int86(&reg86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }

  //ah register is set to 0 if everything was sucessful
  if(reg86.u.b.ah != 0)
    return 1;

  return 0;
}


int get_vram_info(uint16_t mode){

  vbe_mode_info_t vmi_p;

  if(vbe_get_info_about_mode(mode, &vmi_p) != 0)
    return 1;

  h_res = vmi_p.XResolution; //updates hor resolution
  v_res = vmi_p.YResolution;  //updates vert resolution
  bits_per_pixel = vmi_p.BitsPerPixel; //updates the bits per pixel
  vram_base = vmi_p.PhysBasePtr;  //updates the vram physical address
  color_mode = vmi_p.MemoryModel; //updates the color mode
  
  RedMaskSize = vmi_p.RedMaskSize;
  RedFieldPosition = vmi_p.RedFieldPosition;
  GreenMaskSize = vmi_p.GreenMaskSize;
  GreenFieldPosition = vmi_p.GreenFieldPosition;
  BlueMaskSize = vmi_p.BlueMaskSize;
  BlueFieldPosition = vmi_p.BlueFieldPosition;

  bytes_per_pixel = bits_per_pixel;

  //number is not even
  if((bytes_per_pixel % 2) != 0)
    bytes_per_pixel++;

  bytes_per_pixel /= 8;

  vram_size = h_res * v_res * bytes_per_pixel; //updates the vram's size


  return 0;
}


int map_memory(){

  /* Allow memory mapping */

  mr.mr_base = (phys_bytes) vram_base;	
  mr.mr_limit = mr.mr_base + vram_size;  

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))){
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    return 1;
  }
  /* Map memory */

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

  if(video_mem == MAP_FAILED){

   panic("couldn't map video memory");
   return 1;
  }

  double_buffer = malloc(vram_size);

  return 0;

}



void* (vg_init)(uint16_t mode){

    if(get_vram_info(mode) != 0)
      return NULL;

    if(map_memory() != 0)
      return NULL;

    if(set_graph_mode(mode) != 0)
      return NULL;

    return video_mem;
}



int color_pixel(uint16_t x, uint16_t y, uint32_t color){

  uint8_t* ptr = video_mem;

  //puts the pointer on the desired line
  ptr += (get_h_res() * y * get_bytespp());

  //puts the pointer on the desired pixel
  ptr += (x * get_bytespp());

  //writes the color value in the given pixel
  for(unsigned j = 0; j < get_bytespp(); j++, ptr++){

    *ptr = (uint8_t)(color >> j * 8);
  }

  return 0;
}

int color_pixel_db(uint16_t x, uint16_t y, uint32_t color){

  uint8_t* ptr = double_buffer;

  //puts the pointer on the desired line
  ptr += (get_h_res() * y * get_bytespp());

  //puts the pointer on the desired pixel
  ptr += (x * get_bytespp());

  //writes the color value in the given pixel
  for(unsigned j = 0; j < get_bytespp(); j++, ptr++){

    *ptr = (uint8_t)(color >> j * 8);
  }

  return 0;
}


int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){

  //draws the line
  for(unsigned i = 0; i < len; i++){
   
      //we have reached the limit of the screen
      if((x + i) >= get_h_res())
        break;

      if(color_pixel(x + i, y, color) != 0){

        printf("Drawing of the line failed!\n");
        return 1;
     }

  }

    return 0;
}



int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){

  color = get_less_bits(color, bits_per_pixel);

  for(unsigned i = 0; i < height; i++){

    //we have reached the limit of the screen
    if((y + i) >= get_v_res())
      break;

    if(vg_draw_hline(x, y + i, width, color) != 0)
      return 1;
  
  }

  return 0;
}


uint8_t return_color_comp(unsigned field_position, unsigned mask_size, uint32_t color){

  uint32_t newC = color >> field_position;
  
  return (uint8_t) (get_less_bits(newC, mask_size));
}


uint32_t change_color(uint16_t row, uint16_t col, uint8_t no_rectangles, uint32_t first, uint8_t step){

  //for indexed color mode
  if(color_mode == INDEX_CLR_MODE){

    uint32_t color = ((first + (row * no_rectangles + col) * step) % (1 << bits_per_pixel));

    return color;

  } //for direct color mode
  else if(color_mode == DIR_CLR_MODE){

    uint8_t redComp = return_color_comp(RedFieldPosition, RedMaskSize, first);
    uint8_t greenComp = return_color_comp(GreenFieldPosition, GreenMaskSize, first);
    uint8_t blueComp = return_color_comp(BlueFieldPosition, BlueMaskSize, first);

    uint8_t redPart = (redComp + col * step) % (1 << RedMaskSize);
    uint8_t greenPart = (greenComp + row * step) % (1 << GreenMaskSize);
    uint8_t bluePart = (blueComp + (col + row) * step) % (1 << BlueMaskSize);

    uint32_t finalColor = (redPart << RedFieldPosition) | (greenPart << GreenFieldPosition) | (bluePart << BlueFieldPosition);

    return finalColor;
  }
  else{
    printf("Error with the color mode! (Not index nor direct\n");
    return 1;

  }

}

int clear_screen(){
 
  uint8_t* ptr = video_mem;

 for (unsigned i=0 ; i < h_res*v_res ; i++)
    *(ptr +i) = 0;

    return 0;
}

int clear_db(){
 
  memset(double_buffer, 0, vram_size);
  return 0;
}


void copy_db(char* colors){
  memcpy(double_buffer, colors, vram_size);
}


void copy_line_db(char* colors, int line_index){
  memcpy((char*)double_buffer + (line_index * get_h_res() * get_bytespp()), colors, get_h_res() * get_bytespp());
}


uint32_t get_less_bits(uint32_t value, uint32_t num_bits){

  value <<= (32 - num_bits);
  value >>= (32 - num_bits);

  return value;
}


int draw_pixmap(const char* sprite, uint16_t x, uint16_t y, int width, int height){

  //FOR MODE 0X115!!
  for(int i = 0; i < height; i++){

    //we have reached the limit of the screen
    if((unsigned) (y + i) >= get_v_res())
      break;

    for(int  j = 0; j < width; j++){
      
      //we have reached the limit of the screen
      if((unsigned) (x + j) >= get_h_res())
        break;
      
      uint32_t color = 0;
      memcpy(&color, &sprite[get_bytespp()*(i*width + j)], get_bytespp());

      //transparent
      if(color == CHROMA_KEY_GREEN_888)
        continue;

      if(color_pixel(x + j, y + i, color) != 0){

        printf("Drawing of the pixmap failed!\n");
        return 1;
     }

    }

 }
  return 0;
}


int draw_pixmap_db(const char* sprite, int x, int y, int width, int height){

  //FOR MODE 0X115!!  
  for(int i = 0; i < height; i++){

    if((y + i) < 0)
      continue;

    //we have reached the limit of the screen
    if((y + i) >= (int) get_v_res()){
      break;
    }

    for(int j = 0; j < width; j++){

      if((x + j) < 0)
        continue;

      //we have reached the limit of the screen
      if((x + j) >= (int) get_h_res())
        break;
      
      uint32_t color = 0;
      memcpy(&color, &sprite[get_bytespp()*(i*width + j)], get_bytespp());

      //transparent
      if(color == CHROMA_KEY_GREEN_888)
        continue;
        

      if(color_pixel_db(x + j, y + i, color) != 0){

        printf("Drawing of the pixmap failed!\n");
        return 1;
     }

    }

 }
  return 0;
}

//-------------------

bool check_pixel_transp(char* pixmap, int x, int y, int width){

      uint32_t color = 0;
      memcpy(&color, &pixmap[get_bytespp()*(y*width + x)], get_bytespp());

      //transparent
      if(color == CHROMA_KEY_GREEN_888)
        return true;
      else return false;
}

//-------------------

int erase_pixmap(uint16_t x, uint16_t y, int width, int height){

for(int i = 0; i < height; i++){

    //we have reached the limit of the screen
    if((unsigned) (y + i) >= get_v_res())
      break;

    for(int  j = 0; j < width; j++){
      
      //we have reached the limit of the screen
      if((unsigned) (x + j) >= get_h_res())
        break;

      if(color_pixel(x + j, y + i, 0) != 0){

        printf("Drawing of the pixmap failed!\n");
        return 1;
     }

    }

 }
  return 0;
}



int vbe_get_ctrl_info(vg_vbe_contr_info_t *ctrl_info, vbe_info_block_t* info_block){

  void* mem_ptr = lm_init(false);

  if(mem_ptr == NULL){
    printf("lm_init failed!\n");
    return 1;
  }

  phys_bytes buf;
  mmap_t map;
  struct reg86u reg86;

  //inicializes VBESignature field, so that info returned is compatible with VBE 2.0
  info_block->VBESignature[0] = 'V';
  info_block->VBESignature[1] = 'B';
  info_block->VBESignature[2] = 'E';
  info_block->VBESignature[3] = '2';

  memset(&reg86, 0, sizeof(reg86)); //clears the structure

  unsigned num_tries = 0;

  //tries to use lm_alloc(); if it fails a max number of times, terminates the program
  while(num_tries < ALLOC_MAX_TRIES){

    if(lm_alloc(sizeof(vbe_info_block_t), &map) == NULL)
      num_tries++;
    else{
      num_tries = 0;
      break;
    }
  }

  if(num_tries == ALLOC_MAX_TRIES){
    printf("lm_alloc failed!\n");
    return 1;
  }

  buf = map.phys;

  reg86.u.b.intno = VID_CARD_I_VEC;
  reg86.u.w.ax = GET_VBE_CTRL_INFO; //0x4F00
  reg86.u.w.es = PB2BASE(buf);
  reg86.u.w.di = PB2OFF(buf);

  if( sys_int86(&reg86) != OK ) {
    printf("\tvg_exit(): sys_int86() failed \n");
    return 1;
  }

  //ah register is set to 0 if everything was sucessful
  if(reg86.u.b.ah != 0)
    return 1;

  //the struct variable now has all the information needed  
  *info_block = *((vbe_info_block_t*) map.virt);

  if(!lm_free(&map)){
    printf("lm_free failed!\n");
    return 1;
  }

  //the struct created by us now has all the information. We need to parse it and put the relevant fields in the vg_vbe_contr_info_t struct.
  strcpy(ctrl_info->VBESignature, info_block->VBESignature);

  ctrl_info->VBEVersion[0] = info_block->VBEVersion[0];
  ctrl_info->VBEVersion[1] = info_block->VBEVersion[1];
  
  ctrl_info->TotalMemory = (uint32_t) info_block->TotalMemory * 64;

  uint32_t address1 = info_block->OEMStringPtr;
  uint32_t offset1 = get_less_bits(address1, 16);
  address1 >>= 16;
  uint32_t base1 = get_less_bits(address1, 16);
  ctrl_info->OEMString = (char*) mem_ptr;
  ctrl_info->OEMString += ((base1 << 4) + offset1);

  uint32_t address2 = info_block->VideoModeList;
  uint32_t offset2 = get_less_bits(address2, 16);
  address2 >>= 16;
  uint32_t base2 = get_less_bits(address2, 16);
  char* ptr = (char*) mem_ptr;
  ptr += ((base2 << 4) + offset2);
  ctrl_info->VideoModeList = (uint16_t*) ptr;

  uint32_t address3 = info_block->OemVendorNamePtr;
  uint32_t offset3 = get_less_bits(address3, 16);
  address3 >>= 16;
  uint32_t base3 = get_less_bits(address3, 16);
  ctrl_info->OEMVendorNamePtr = (char*) mem_ptr;
  ctrl_info->OEMVendorNamePtr += ((base3 << 4) + offset3);

  uint32_t address4 = info_block->OemProductNamePtr;
  uint32_t offset4 = get_less_bits(address4, 16);
  address4 >>= 16;
  uint32_t base4 = get_less_bits(address4, 16);
  ctrl_info->OEMProductNamePtr = (char*) mem_ptr;
  ctrl_info->OEMProductNamePtr += ((base4 << 4) + offset4);

  uint32_t address5 = info_block->OemProductRevPtr;
  uint32_t offset5 = get_less_bits(address5, 16);
  address5 >>= 16;
  uint32_t base5 = get_less_bits(address5, 16);
  ctrl_info->OEMProductRevPtr = (char*) mem_ptr;
  ctrl_info->OEMProductRevPtr += ((base5 << 4) + offset5);

  return 0;
}
