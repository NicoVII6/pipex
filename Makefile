SRCS = pipex_utils.c main.c \
	pipex_utils_libft.c split_libft.c handle_errors.c \
	cmd_paths_control.c \

OBJS = ${SRCS:.c=.o}

NAME = pipex

CC = gcc

# the '-f' flag ensures that files are forcefully removed without
# generating error msg if they do not exist
RM = rm -f

CFLAGS = -Wall -Wextra -Werror

# utile pour la derniere commande re
all : $(NAME)

# compiling a '.c' file into an object file '.o', same thing as '%.o = %.c'
.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
# the '$<' represents the source file, and '${<:.c=.o} replaces the extension
# in the source file to '.o'

${NAME}: ${OBJS}
	$(CC) ${OBJS} $(CFLAGS) -o $(NAME)
# the flag '-o $(NAME) indicates the name of the output file which is the name
# of the executable to be generated.

# clean the project
clean:
	rm -f ${OBJS}

# clean the project including the executable
fclean: clean
	rm -f $(NAME)

# clean all the project and rebuild it
re: fclean all