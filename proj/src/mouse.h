#pragma once
#include <stdbool.h>
#include <stdint.h>

/** @defgroup mouse mouse
 * @{
 * Functions for manipulating the kbc controller for the mouse
 */


/**
 * @brief Subscribes the mouse interrupts on exclusive mode (meaning that the Minix IH is disabled)
 * 
 * @param bit_no Bit number
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int mouse_subscribe_int(uint8_t *bit_no);


/**
 * @brief Unsubscribes mouse interrupts
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int mouse_unsubscribe_int();


/**
 * @brief Checks if bit 3 of a byte is set, to see if we are reading the first byte of a data packet
 * 
 * @param byte Packet byte
 *  
 * @return True if it is the first byte, false otherwise
 */
bool check_if_first_byte(uint8_t byte);


/**
 * @brief Reads a return value from the KBC; used if the information is coming from the mouse (used after issuing a command that asks for a return value)
 * 
 * @param ret Value returned
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int read_ret_value_mouse(uint8_t *ret);


/**
 * @brief Disables interrupts for the mouse
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int disable_mouse_int();


/**
 * @brief Issues a mouse command via the command 0xD4
 * 
 * @param mouse_cmd Command to be issued
 * @param ackByte Acknowledgement byte
 * 
 * @return 1 if some error ocurred, 0 otherwise
 */
int issue_mouse_cmd(uint8_t mouse_cmd, uint8_t *ackByte);


/**
 * @brief Given a delta value in 2´s complement and the bit sign of that value, returns the decimal value
 * 
 * @param delta Delta value in 2's complement
 * @param sign False if it is a positive number, true if it is negative
 * 
 * @return Decimal value
 */
int16_t convert2sComp(uint8_t delta, bool sign);


/**
 * @brief Function that receives a full packet (with the 3 bytes) and parses the information
 * 
 * @param pp Packet struct
 * 
 * @return 0, indicating no error ocurred
 */
int parse_packet(struct packet *pp);


/**
 * @brief Function that just returns the absolute value of a given value
 * 
 * @param value Value
 * 
 * @return Absolute value
 */
int absValue(int value);


/* enumeration type decribing the different states of the higher level of the state machine */
typedef enum states{ INITIAL, DRAWING_L, MIDDLE, DRAWING_R, COMPLETE} state_st;

/* enumeration type describing the different states of the lower level of the state machine */
typedef enum lower_lev_states {NO_BUT_PRESSED, LB_PR, RB_PR, OTHER_BUT_COMB} ll_state;

struct state_machine{

  state_st currentState; //current state of the state machine
  int x_displacement; //current displacement in the x direction
  int y_displacement; //current displacement in the y direction

};


/**
 * @brief Function that changes the state of the higher level state machine, if an event ocurred
 * 
 * @param event_st The event
 * @param st The current state
 * @param x_len X length
 * @param tolerance Tolerance
 */
void mouse_event_handler(struct mouse_ev event_st, struct state_machine *st, uint8_t x_len, uint8_t tolerance);


/**
 * @brief Function that detects mouse events, from the information of the current packet and the lower level state machine
 * 
 * @param pp Packet struct
 * @param event_st The event
 */
void mouse_event_detect(struct packet *pp, struct mouse_ev *event_st);


/** @} end of mouse */
