CC	= cc -g3

RM	= rm -f

NAME	= libjsh.so

CFLAGS 	= -I./include -I../include -fPIC

SRC	=	src/other/version.c \
		src/other/echo.c \
		src/other/cd.c \
		src/env/env.c\
		src/env/setenv.c\
		src/env/unsetenv.c\

OBJS	= $(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
	cc -shared -Wl,-soname,$(NAME) -o $(NAME) $(OBJS)
	cp $(NAME) /lib

clean:	
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all
