#include <machine/asm.h>

.global _C_LABEL(global_int_counter)
.global _C_LABEL(timer_asm_ih)

.text

/* void timer_int_handler() */

_C_LABEL(timer_asm_ih):

    /* Increment the Timer Interruption Counter */
    incl _C_LABEL(global_int_counter)

    ret
