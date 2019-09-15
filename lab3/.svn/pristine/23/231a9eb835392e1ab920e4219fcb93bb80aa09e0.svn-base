#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <lcom/lcf.h>


//subscribes kbd interrupts on exclusive mode (meaning that the Minix IH is disabled)
int kbd_subscribe_int(uint8_t *bit_no);


//unsubscribes the kbd interrupts
int kbd_unsubscribe_int();


//counts the number of calls of sys_inb (only for lab3, not for the project)
int sys_inb_cnt(port_t port, uint32_t *byte);


//return true if it is a make code; false if break code
int is_make(uint8_t code, bool *make);

//processes the scancode received
int process_scancode(uint8_t bytes[], uint8_t *size, bool *make, bool *twoBytes);

//function that enables the functionality of the keyboard after the polling cycle ends
int keyboard_enable();

//reads the command byte 
int read_command_byte(uint8_t *cmd_byte);

//writes a command byte
int write_command_byte(uint8_t cmd_byte);

//checks, via reading the status register, if it can issue a command; if it can, it issues it
int issue_command(uint8_t cmd);

//checks, via reading the status register, if it can issue a command; if it can,
//it issues it
int issue_arg(uint8_t cmd);

//reads a return value from the KBC (used after issuing a command that asks for a return value)
int read_ret_value(uint8_t *ret);

extern void (kbc_asm_ih)();
extern uint8_t key_code;
extern bool ih_check;
