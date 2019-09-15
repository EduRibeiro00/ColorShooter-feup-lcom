#include <machine/asm.h>
#include "i8042.h"

.global _C_LABEL(mouse_asm_ih)
.global _C_LABEL(packet_byte)
.global _C_LABEL(mouse_ih_check)

.data
_C_LABEL(packet_byte):
.byte 0

_C_LABEL(mouse_ih_check):
.byte 0

.text
_C_LABEL(mouse_asm_ih):
  inb $STAT_REG, %al  /*reads the status register*/

  test $OBF, %al  /*checks if the output buffer is full*/

  jz ERROR

  TEST $PAR_ERR, %al  /*checks for a parity error*/
  jnz ERROR

  test $TO_ERR, %al  /*checks for a timeout errror*/
  jnz ERROR

  inb $OUT_BUF, %al /*reads the output buffer */

  movb %al, _C_LABEL(packet_byte)  /*places content in packet byte*/

  movl $1, _C_LABEL(mouse_ih_check) /* returns true */

  jmp END

ERROR:
  movl $0, _C_LABEL(mouse_ih_check) /*An error happened, return false */

END: 
  ret
