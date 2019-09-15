#pragma once
#include <stdbool.h>
#include <stdint.h>

/** @defgroup video video
 * @{
 * Functions for manipulating the video graphics card
 */


/**
 * @brief Returns the horizontal resolution in pixels
 * 
 * @return The horizontal resolution
 */
unsigned get_h_res();


/**
 * @brief Returns the vertical resolution in pixels
 * 
 * @return The vertical resolution
 */
unsigned get_v_res();


/**
 * @brief Returns the number of VRAM bits per pixel
 * 
 * @return Number of VRAM bits per pixel
 */
unsigned get_bitspp();


/**
 * @brief Returns the number of VRAM bytes per pixel
 * 
 * @return Number of VRAM bytes per pixel
 */
unsigned get_bytespp();


/**
 * @brief Returns the struct with the information about minix's memory range
 * 
 * @return Struct with the information about minix's memory range
 */
struct minix_mem_range get_minix_memory_range();


/**
 * @brief Returns VRAM's physical address
 * 
 * @return VRAM's physical address
 */
unsigned int get_vram_base();


/**
 * @brief Returns VRAM's size
 * 
 * @return The VRAM's size
 */
unsigned int get_vram_size();


/**
 * @brief Return the video memory pointer
 * 
 * @return The video memory pointer
 */
void* get_video_mem();


/**
 * @brief Return the double buffer
 * 
 * @return The double buffer
 */
void* get_db();


/**
 * @brief Returns the color mode
 * 
 * @return The color mode
 */
unsigned get_color_mode();


/**
 * @brief Passes the information in the double buffer to the video memory
 */
void DBtoVM();


/**
 * @brief Sets the desired graphical mode
 * 
 * @param mode Graphical mode
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int set_graph_mode(uint16_t mode);


/**
 * @brief Function that maps the vram physical memory into the process's virtual memory, given the information in the static global variables
 * 
 * @return 1 if some error ocurred, 0 otherwise 
 */
int map_memory();


/**
 * @brief Gets the vram physical address, and updates the static variables accordingly
 * 
 * @param mode The graphical mode used
 * 
 * @return 1 if some error ocurred, 0 otherwise  
 */
int get_vram_info(uint16_t mode);


/**
 * @brief function that returns the least significant bits of a 32-bit value
 * 
 * @param value 32-bit value
 * @param num_bits Number of bits we want
 * 
 * @return The least significant bits of the 32-bit value 
 */
uint32_t get_less_bits(uint32_t value, uint32_t num_bits);


/**
 * @brief Function that just colors in a pixel, situated at the given coordinates
 * 
 * @param x X coordinate of the pixel
 * @param y Y coordinate of the pixel
 * @param color New color for the pixel
 *  
 * @return 0, indicating no error ocurred 
 */
int color_pixel(uint16_t x, uint16_t y, uint32_t color);


/**
 * @brief Function that colors in a pixel in the double buffer
 * 
 * @param x X coordinate of the pixel
 * @param y Y coordinate of the pixel
 * @param color New color for the pixel
 * 
 * @return 0, indicating no error ocurred
 */
int color_pixel_db(uint16_t x, uint16_t y, uint32_t color);


/**
 * @brief Function that gets the right color for a rectangle, given its coordinates, the first color, the step and the no of rectangles (used in video_test_pattern)
 * 
 * @param row Row
 * @param col column
 * @param no_rectangles Number of rectangles
 * @param first First color
 * @param step Step used
 * 
 * @return The right color for the rectangle
 */
uint32_t change_color(uint16_t row, uint16_t col, uint8_t no_rectangles, uint32_t first, uint8_t step);


/**
 * @brief Returns a certain color component, given its field position and mask size
 * 
 * @param field_position Filed position
 * @param mask_size Mask size
 * @param color Color
 * 
 * @return The desired color component
 */
uint8_t return_color_comp(unsigned field_position, unsigned mask_size, uint32_t color);


/**
 * @brief Draws a pixmap on the screen, on the given coordinates (does not draw when the color is transparent)
 * 
 * @param sprite The pixmap
 * @param x X coordinate
 * @param y Y coordinate
 * @param width Width of the pixmap
 * @param height Height of the pixmap
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int draw_pixmap(const char* sprite, uint16_t x, uint16_t y, int width, int height);

/**
 * @brief Draws a pixmap on the double buffer, on the given coordinates (does not draw when the color is transparent)
 * 
 * @param sprite The pixmap
 * @param x X coordinate
 * @param y Y coordinate
 * @param width Width of the pixmap
 * @param height Height of the pixmap
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int draw_pixmap_db(const char* sprite, int x, int y, int width, int height);


/**
 * @brief Erases a pixmap that is on the screen, given its coordinates
 * 
 * @param x X coordinate
 * @param y Y coordinate
 * @param width Width of the pixmap
 * @param height Height of the pixmap
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int erase_pixmap(uint16_t x, uint16_t y, int width, int height);


/**
 * @brief Function that gets the information about the current graphical mode
 * 
 * @param mode Graphical mode
 * @param vmi_p VBE mode info pointer
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int vbe_get_info_about_mode(uint16_t mode, vbe_mode_info_t *vmi_p);


/**
 * @brief Clears the screen
 * 
 * @return 0, indicating no error ocurred
 */
int clear_screen();


/**
 * @brief Clears the double buffer
 * 
 * @return 0, indicating no error ocurred
 */
int clear_db();


/**
 * @brief Copies, using memcpy, to the double buffer
 * 
 * @param colors The color bytes to be copied to the double buffer
 */
void copy_db(char* colors);


/**
 * @brief Copies, using memcpy, a line to the double buffer
 * 
 * @param colors The color bytes to be copied to the double buffer
 * @param line_index Specifies what line of the double buffer is going to be updated
 */
void copy_line_db(char* colors, int line_index);


/**
 * @brief Checks if a certain pixel is transparent or not
 * 
 * @param pixmap The pixmap
 * @param x X coordinate of the pixel, in the pixmap
 * @param y Y coordinate of the pixel, in the pixmap
 * @param width Width of the pixmap
 * 
 * @return True if the pixel is transparent, false otherwise
 */
bool check_pixel_transp(char* pixmap, int x, int y, int width);


#pragma pack(1)

typedef struct {
    char VBESignature[4];   
    BCD VBEVersion[2];          
    uint32_t OEMStringPtr;               
    uint8_t Capabilities[4];                
    uint32_t VideoModeList;      
    uint16_t TotalMemory;            

    uint16_t OemSoftwareRev;                 
    uint32_t OemVendorNamePtr;
    uint32_t OemProductNamePtr;
    uint32_t OemProductRevPtr;  
    uint8_t Reserved[222];            
    uint8_t OemData[256];

}  vbe_info_block_t;

#pragma options align=reset

/**
 * @brief Function that calls VBE function 0x4F00, to get controller information
 * 
 * @param ctrl_info Pointer to struct vg_vbe_contr_info_t
 * @param info_block Pointer to struct vbe_info_block_t
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int vbe_get_ctrl_info(vg_vbe_contr_info_t *ctrl_info, vbe_info_block_t* info_block);


/** @} end of video */
