NAME = miniRT
SOURCE = source/
SRCS = $(shell find $(SOURCE) -name '*.c')
OBJS = $(SRCS:.c=.o)
LIBFT = includes/libft/libft.a
LIBX = includes/42mlx/libmlx.a
LIBX_OBJ = includes/42mlx/obj
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBX)
	   cc $(SRCS) -I includes -o $(NAME)

$(LIBFT):
	make -C includes/libft

$(LIBX):
	make -C includes/42mlx

clean:
	rm -r -f $(LIBX_OBJ)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re