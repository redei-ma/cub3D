
CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L./includes/mlx -lmlx -lXext -lX11 -lm -lz

NAME = cub3d

LIBFT_DIR = ./includes/libft
LIBFT = includes/libft/libft.a
MINILIBX_DIR = includes/mlx

INCLUDES = includes/mlx/libmlx.a
SRC = parsing/parsing.c\
		parsing/get_elements.c \
		parsing/free_vari.c \
		parsing/get_map.c \
		parsing/ft_split_len.c \
		parsing/validate_map.c \
		parsing/ft_countlines.c \
		main.c \


OBJ = $(SRC:.c=.o)

all: $(NAME)

mlx:
	git clone https://github.com/42Paris/minilibx-linux.git ./includes/mlx
	make -C ./includes/mlx

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(MINILIBX_DIR)/libmlx.a:
	@$(MAKE) -C $(MINILIBX_DIR) --quiet

$(NAME): $(OBJ) $(LIBFT) $(MINILIBX_DIR)/libmlx.a
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LFLAGS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I$(CURDIR) -I$(MINILIBX_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean --quiet
	@$(MAKE) -C $(MINILIBX_DIR) clean --quiet

fclean: clean
	rm -rf $(NAME)
	rm -rf ./includes/mlx
	@$(MAKE) -C $(LIBFT_DIR) fclean --quiet

re: fclean all

.PHONY: all clean fclean re
