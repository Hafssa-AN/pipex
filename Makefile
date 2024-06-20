NAME = pipex.a

NAMEB = pipex_bonus.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

rm = rm -rf

HEADER = ./includes/pipex.h

HEADER_BONUS = ./includes/pipex_bonus.h

SRCS = ./mandatory/main.c ./mandatory/libft.c ./mandatory/path.c ./mandatory/proc.c

BONUS = ./bonus/main_bonus.c ./bonus/errors_bonus.c ./bonus/get_next_line.c  \
		./bonus/here_doc_bonus.c ./bonus/libft.c ./bonus/path_bonus.c  ./bonus/tools.c

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(NAMEB): $(BONUS_OBJS) $(HEADER_BONUS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(NAMEB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAMEB)

clean:
	$(rm) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(rm) $(OBJS) $(BONUS_OBJS)

re: fclean all

.PHONY: all clean fclean re bonus