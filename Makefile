NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -lXext -lX11 -lm -lz

SRCS =	srcs/main.c \
		srcs/dda.c \
		srcs/init.c \
		srcs/drawing.c \
		srcs/movement.c \
		srcs/events.c

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
MINILIBX_DIR = ./minilibx-linux
MINILIBX = $(MINILIBX_DIR)/libmlx.a
MLX_REPO = https://github.com/42Paris/minilibx-linux.git

all: $(NAME)

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(MINILIBX):
	@echo "Cloning MinilibX..."
	@git clone $(MLX_REPO) $(MINILIBX_DIR) --quiet
	@echo "Compiling MinilibX..."
	@$(MAKE) -C $(MINILIBX_DIR) --quiet

$(NAME): $(LIBFT) $(MINILIBX) $(SRCS)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(MINILIBX) $(MLXFLAGS) -Iinclude -o $(NAME)

clean:
	@echo "Removing object files..."
	@$(MAKE) -C $(LIBFT_DIR) clean --quiet
	@$(MAKE) -C $(MINILIBX_DIR) clean --quiet

fclean: clean
	@echo "Removing library and executables..."
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --quiet
	@rm -rf $(MINILIBX_DIR)

re: fclean all

.PHONY: all clean fclean re
.SILENT:
