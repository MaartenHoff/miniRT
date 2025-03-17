NAME	= miniRT
SOURCE	= source
OBJDIR	= .obj
SRCS	= $(shell find $(SOURCE) -name '*.c')
OBJS	= $(SRCS:$(SOURCE)/%.c=$(OBJDIR)/%.o)
LIBFT	= includes/libft/libft.a
LIBX	= includes/42mlx/libmlx.a

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -Iincludes -O3
LDFLAGS	= -Lincludes/libft -lft -Lincludes/42mlx -lmlx -lm -lX11 -lXext

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBX)
		$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SOURCE)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(dir $(LIBFT))

$(LIBX):
	$(MAKE) -C $(dir $(LIBX))

clean:
	$(MAKE) -C $(dir $(LIBFT)) clean
	$(MAKE) -C $(dir $(LIBX)) clean
	rm -rf $(OBJDIR)

fclean: clean
	$(MAKE) -C $(dir $(LIBFT)) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re