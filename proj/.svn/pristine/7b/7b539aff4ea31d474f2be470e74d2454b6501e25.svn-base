#ifndef _I8042_H_
#define _I8042_H_

#define BIT(n)  (0x01<<(n))
#define DELAY_US    20000
#define MAX_WAIT    5  //we decided to wait 5 cycles before giving up on command byte operations

//registers
#define STAT_REG        0x64   //status register
#define IN_BUF_CMD      0x64   //to send commands to the input buffer
#define IN_BUF_ARGS     0x60   //to send arguments to the input buffer
#define OUT_BUF         0x60   //output buffer

//bit values
#define OBF             BIT(0)
#define IBF             BIT(1)
#define PAR_ERR         BIT(7)
#define TO_ERR          BIT(6)
#define KBD_ENABLE_BIT  BIT(0)
#define AUX             BIT(5)


//command values
#define READ_CMD_BYTE   0x20
#define WRITE_CMD_BYTE  0x60


//key values
#define ESC_BRK_CODE  0x81  //the break code of the 'ESC' key
#define TWO_BYTE_ID   0xe0  //the first byte of all two byte scancodes


//mouse macros
#define MOUSE_IRQ   12

//bit values
#define FIRST_BYTE_ID BIT(3) //used to check if bit 3 of a certain byte is set (useful for checking                              //if we are reading the first byte of a data packet)

#define MOUSE_ENABLE_BIT  BIT(1) //to enable mouse interrupts (change the command byte)

//command values for the mouse
#define ENB_MOUSE         0xA8  //command to enable the mouse
#define DIS_MOUSE         0xA7  //command to disable the mouse
#define WRITE_BYTE_MOUSE  0xD4  //command used to issue a byte directly to the mouse (passed as arg)

//commands passed as arguments of command 0xD4 (WRITE_BYTE_MOUSE)
#define ENB_DATA_REP      0xF4  //enable data reporting (stream mode only)
#define DIS_DATA_REP      0xF5  //disable data reporting (stream mode only)
#define SET_STRM_MODE     0xEA  //sets stream mode
#define SET_RMT_MODE      0xF0  //sets remote mode
#define READ_DATA         0xEB  //send data packet request
#define RESEND            0xFE  //resends a byte (used when the response is a NACK)

//other values
#define ACK                  0xFA  //byte send after mouse command; sent if everything OK
#define NACK                 0xFE  //byte send after mouse command; sent if invalid byte
#define ERROR                0xFC  //byte send after mouse command; sent if 2nd consecutive inv byte
#define DIS_INT_MOUSE_BYTE   0xFD  //bit 1 is 0; used to disable mouse ints via command byte

//mouse packet macros
#define MOUSE_LB      BIT(0)
#define MOUSE_RB      BIT(1)
#define MOUSE_MB      BIT(2)
#define MOUSE_X_SIGN  BIT(4)
#define MOUSE_Y_SIGN  BIT(5)
#define MOUSE_X_OV    BIT(6)
#define MOUSE_Y_OV    BIT(7)

#endif
