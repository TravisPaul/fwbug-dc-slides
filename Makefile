PROG=	fwbug1
SRCS=	main.c 
MAN=	fwbug1.6
DPADD=  ${LIBCURSES} ${LIBTERMINFO}
LDADD=  -lcurses -lterminfo

.include <bsd.prog.mk>
