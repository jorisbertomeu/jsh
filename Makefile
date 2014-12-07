CC	= cc -g3

RM	= rm -f

NAME	= jSh

CFLAGS 	= -I./include

SRC	= src/main.c

OBJS	= $(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
	cc -o $(NAME) -ldl $(OBJS)

clean:	
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all
