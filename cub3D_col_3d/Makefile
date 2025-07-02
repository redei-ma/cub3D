NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -lXext -lX11 -lm -lz
VALGRIND = valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes

SRCS =	srcs/parsing/parsing.c\
		srcs/parsing/get_elements.c \
		srcs/parsing/free_vari.c \
		srcs/parsing/get_map.c \
		srcs/parsing/ft_split_len.c \
		srcs/parsing/validate_map.c \
		srcs/parsing/ft_strjoin_m.c \
		srcs/parsing/check_all_characters_are_present.c \
		srcs/parsing/get_colors.c \
		srcs/parsing/get_texture.c \
		srcs/parsing/create_map_line.c \
		srcs/main.c \
		srcs/dda.c \
		srcs/init.c \
		srcs/drawing.c \
		srcs/drawing_3d.c \
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
	@if [ ! -d "$(MINILIBX_DIR)" ]; then \
		echo "Cloning MinilibX..."; \
		git clone $(MLX_REPO) $(MINILIBX_DIR) --quiet; \
	fi
	@echo "Compiling MinilibX..."
	@$(MAKE) -C $(MINILIBX_DIR) --quiet

$(NAME): $(LIBFT) $(MINILIBX) $(SRCS)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(MINILIBX) $(MLXFLAGS) -Iinclude -o $(NAME)

val: $(NAME)
	$(VALGRIND) ./$(NAME) $(ARGS)

clean:
	@echo "Removing object files..."
	@$(MAKE) -C $(LIBFT_DIR) clean --quiet
	$(MAKE) -C $(MINILIBX_DIR) clean --quiet

fclean: clean
	@echo "Removing library and executables..."
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --quiet
	rm -rf $(MINILIBX_DIR)

re: fclean all

.PHONY: all clean fclean re
.SILENT:
