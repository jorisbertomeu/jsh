CC	= gcc -g3

RM	= rm -f

NAME	= libjsh.so

CFLAGS 	= -I./include -I../include -fPIC `curl-config --cflags`

SRC	=	src/other/version.c \
		src/other/echo.c \
		src/other/cd.c \
		src/env/env.c\
		src/env/setenv.c\
		src/env/unsetenv.c\
		src/alias/alias.c \
		src/alias/alias_add.c\
		src/alias/alias_list.c \
		src/social/social.c\
		src/social/connect.c\
		src/social/profile.c\
		src/jmanager/jmanager.c\
		src/jmanager/jmanager_add.c\
		src/jmanager/jmanager_list.c\
		src/json/json.c\

OBJS	= $(SRC:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
	#gcc -shared -Wl,-install_name,$(NAME), -o $(NAME) $(OBJS)
	cc -shared -Wl,-soname=$(NAME) -o $(NAME) `curl-config --libs` $(OBJS) -lcurl
	cp $(NAME) /usr/lib/

mac:		$(NAME)
	gcc -shared $(OBJS) -lc -Wl,-install_name,$(NAME), -o $(NAME)
	cp $(NAME) /lib

clean:	
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:		fclean all
