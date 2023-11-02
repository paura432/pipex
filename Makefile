NAME = pipex

MY_SOURCES = pipex.c pipex_utils.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ilibreria #-g3 -fsanitize=address

all: ${NAME}
${NAME}: ${MY_OBJECTS}
	@${MAKE} -C ./Libft
	@${CC} ${CFLAGS} ${MY_OBJECTS} ./Libft/libft.a -o ${NAME}

clean:
		@${MAKE} -C ./libft fclean
		rm -f $(MY_OBJECTS)

fclean: clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all, clean, fclean, re
