PROG=	fwbug1
SRCS=	main.c 
MAN=    fwbug1.6
DPADD=  ${LIBCURSES}
LDADD=  -lcurses

.include <bsd.prog.mk>
