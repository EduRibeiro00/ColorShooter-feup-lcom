#pragma once
#include <stdbool.h>
#include <stdint.h>

//subscribes the mouse interrupts on exclusive mode (meaning that the Minix IH is disabled)
int mouse_subscribe_int(uint8_t *bit_no);

//unsubscribes mouse interrupts
int mouse_unsubscribe_int();

//checks if bit 3 of a byte is set, to see if we are reading the first byte of a data packet
bool check_if_first_byte(uint8_t byte);

//reads a return value from the KBC; used if the information is coming from the mouse (used after issuing a command that asks for a return value)
int read_ret_value_mouse(uint8_t *ret);

//disables interrupts for the mouse
int disable_mouse_int();

//issues a mouse command via the command 0xD4
int issue_mouse_cmd(uint8_t mouse_cmd, uint8_t *ackByte);

//given a delta value in 2´s complement and the bit sign of that value, returns the decimal value
int16_t convert2sComp(uint8_t delta, bool sign);

//function that receives a full packet (with the 3 bytes) and parses the information
int parse_packet(struct packet *pp);

//function that just returns the absolute value of a given value
int absValue(int value);

//enumeration type decribing the different states of the higher level of the state machine
typedef enum states{ INITIAL, DRAWING_L, MIDDLE, DRAWING_R, COMPLETE} state_st;

//enumeration type describing the different states of the lower level of the state machine
typedef enum lower_lev_states {NO_BUT_PRESSED, LB_PR, RB_PR, OTHER_BUT_COMB} ll_state;

struct state_machine{

  state_st currentState; //current state of the state machine
  int x_displacement; //current displacement in the x direction
  int y_displacement; //current displacement in the y direction

};

//function that changes the state of the higher level state machine, if an event ocurred
void mouse_event_handler(struct mouse_ev event_st, struct state_machine *st, uint8_t x_len, uint8_t tolerance);

//function that detects mouse events, from the information of the current packet and the lower level state machine
void mouse_event_detect(struct packet *pp, struct mouse_ev *event_st);
