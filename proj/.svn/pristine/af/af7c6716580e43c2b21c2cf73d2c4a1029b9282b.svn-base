PROG=proj

SRCS = proj.c sprite.c timer.c keyboard.c mouse.c video.c Cursor.c Bullet.c Game.c Button.c Enemy.c Ships.c rtc.c Highscores.c Explosion.c StateMachine.c kbc_ih.S timer_ih.S mouse_ih.S

CPPFLAGS += -pedantic #-D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF} ${LIBLM}
LDADD += -llcf -llm -lm

.include <minix.lcom.mk>
