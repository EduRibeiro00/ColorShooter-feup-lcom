#pragma once
#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>
#include <minix/sysutil.h>

/** @defgroup keyboard keyboard
 * @{
 * Functions for manipulating the kbc controller for the keyboard
 */


/**
 * @brief Subscribes keyboard interrupts on exclusive mode (meaning that the Minix IH is disabled)
 * 
 * @param bit_no Bit number
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int kbd_subscribe_int(uint8_t *bit_no);


/**
 * @brief Unsubscribes the keyboard interrupts
 * 
 * @return 1 if some error ocurred, 0 otherwise 
 */
int kbd_unsubscribe_int();


/**
 * @brief Counts the number of calls of sys_inb (only for lab3, not for the project)
 * 
 * @param port Port address
 * @param byte Byte address
 * 
 * @return 1 if some error ocurred, 0 otherwise 
 */
int sys_inb_cnt(port_t port, uint32_t *byte);


/**
 * @brief Tells if the key code is a make code or a break code
 * 
 * @param code Key code
 * @param make Will be true if it is a make code; false if it is a break code
 * 
 * @return 0, indicating no error ocurred
 */
int is_make(uint8_t code, bool *make);


/**
 * @brief Processes the scancode received
 * 
 * @param bytes Array with the key code bytes
 * @param size Size of the array
 * @param make If it is a make code or break code
 * @param twoBytes True if the key code has two bytes
 * 
 * @return 0, indicating no error ocurred
 */
int process_scancode(uint8_t bytes[], uint8_t *size, bool *make, bool *twoBytes);


/**
 * @brief Function that enables the functionality of the keyboard after the polling cycle ends
 * 
 * @return 1 if some error ocurred, 0 otherwise  
 */
int keyboard_enable();


/**
 * @brief Reads the command byte 
 * 
 * @param cmd_byte Command byte
 * 
 * @return 1 if some error ocurred, 0 otherwise 
 */
int read_command_byte(uint8_t *cmd_byte);


/**
 * @brief Writes a command byte
 * 
 * @param cmd_byte Command byte
 * 
 * @return 1 if some error ocurred, 0 otherwise 
 */
int write_command_byte(uint8_t cmd_byte);


/**
 * @brief Checks, via reading the status register, if it can issue a command; if it can, it issues it
 * 
 * @param cmd Command to be issued
 * 
 * @return 1 if some error ocurred, 0 otherwise 
 */
int issue_command(uint8_t cmd);


/**
 * @brief Checks, via reading the status register, if it can issue an argument; if it can,it issues it
 * 
 * @param cmd Argument to be issued
 * 
 * @return 1 if some error ocurred, 0 otherwise 
 */
int issue_arg(uint8_t cmd);


/**
 * @brief Reads a return value from the KBC (used after issuing a command that asks for a return value)
 * 
 * @param ret Value returned
 * 
 * @return 1 if some error ocurred, 0 otherwise 
 */
int read_ret_value(uint8_t *ret);


/** @} end of keyboard */
