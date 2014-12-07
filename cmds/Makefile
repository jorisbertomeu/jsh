CC	= gcc -g3

RM	= rm -f

NAME	= libjsh.so

CFLAGS 	= -I./include -I../include -fPIC

SRC	=	src/other/version.c \
		src/other/echo.c \
		src/other/cd.c \
		src/other/alias.c \
		src/env/env.c\
		src/env/setenv.c\
		src/env/unsetenv.c\

OBJS	= $(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
	#gcc -shared -Wl,-install_name,$(NAME), -o $(NAME) $(OBJS)
	cc -shared -Wl,-soname=$(NAME) -o $(NAME) $(OBJS)
	cp $(NAME) /usr/lib/

mac:		$(NAME)
	gcc -shared $(OBJS) -lc -Wl,-install_name,$(NAME), -o $(NAME)
	cp $(NAME) /lib

clean:	
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all
