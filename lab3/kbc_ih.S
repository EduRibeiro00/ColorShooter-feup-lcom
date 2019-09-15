#include <machine/asm.h>
#include "i8042.h"

.global _C_LABEL(kbc_asm_ih)
.global _C_LABEL(key_code)
.global _C_LABEL(ih_check)

.data
_C_LABEL(key_code):
.byte 0

_C_LABEL(ih_check):
.byte 0

.text
_C_LABEL(kbc_asm_ih):
  inb $STAT_REG, %al  /*reads the status register*/

  test $OBF, %al  /*checks if the output buffer is full*/

  jz ERROR

  TEST $PAR_ERR, %al  /*checks for a parity error*/
  jnz ERROR

  test $TO_ERR, %al  /*checks for a timeout errror*/
  jnz ERROR

  inb $OUT_BUF, %al /*reads the output buffer */

  movb %al, _C_LABEL(key_code)  /*places content in scan code*/

  movl $1, _C_LABEL(ih_check) /* returns true */

  jmp END

ERROR:
  movl $0, _C_LABEL(ih_check) /*An error happened, return false */

END: 
  ret




