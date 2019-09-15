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

#endif
