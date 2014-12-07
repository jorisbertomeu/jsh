CC	=	cc -g3

RM	=	rm -f

NAME	=	jSh

CFLAGS 	=	-I./include

SRC	=	src/main.c		\
		src/core/args.c		\
		src/core/core.c		\
		src/core/free.c		\
		src/env/env_core.c	\
		src/feature/loading.c	\
		src/init/memory.c	\
		src/init/parsing.c	\
		src/system/errors.c	\
		src/system/util.c	\

OBJS	=	$(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
		cc -o $(NAME) -ldl $(OBJS)

clean:	
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
