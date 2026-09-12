NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -lXext -lX11 -lm -lz
VALGRIND = valgrind  --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes

SRCS_DIR = srcs
SRCS_FILE =	main.c \
			parsing/parsing.c\
			parsing/get_elements.c \
			parsing/free_utils.c \
			parsing/get_map.c \
			parsing/ft_split_len.c \
			parsing/validate_map.c \
			parsing/ft_strjoin_m.c \
			parsing/check_all_characters_are_present.c \
			parsing/get_colors.c \
			parsing/get_texture.c \
			parsing/create_map_line.c \
			parsing/check_surrounded_by_wall.c \
			init.c \
			events.c \
			mouse_events.c \
			dda.c \
			collision.c \
			movement.c \
			load_textures.c \
			texture_utils.c \
			render_textures.c \
			drawing_3d_utils.c \
			drawing_3d.c \
			drawing_minimap.c \
			drawing.c \
			doors.c
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_FILE))

HDRS = include/cub3D.h include/parsing.h
INCLUDES = -Iinclude -I$(LIBFT_DIR)/include -I$(MINILIBX_DIR)

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

$(NAME): $(LIBFT) $(MINILIBX) $(SRCS) $(HDRS)
	@echo "Compiling $(NAME)..."
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(MINILIBX) $(MLXFLAGS) $(INCLUDES) -o $(NAME)

debug: fclean $(LIBFT) $(MINILIBX)
	@echo "Compiling $(NAME) with debug symbols..."
	@$(CC) $(CFLAGS) -g $(SRCS) $(LIBFT) $(MINILIBX) $(MLXFLAGS) $(INCLUDES) -o $(NAME)

val: $(NAME)
	$(VALGRIND) ./$(NAME) $(ARGS)

clean:
	@echo "Removing object files..."
	@$(MAKE) -C $(LIBFT_DIR) clean --quiet
	@if [ -f $(MINILIBX_DIR)/Makefile.gen ]; then \
		$(MAKE) -C $(MINILIBX_DIR) clean --quiet; fi

fclean: clean
	@echo "Removing build output..."
	@rm -rf $(NAME) $(NAME).dSYM
	@$(MAKE) -C $(LIBFT_DIR) fclean --quiet
	@rm -rf $(MINILIBX)

remove:
	@echo "Removing minilibx directory..."
	@rm -rf $(MINILIBX_DIR)

re: fclean all

.PHONY: all clean fclean remove re debug
.SILENT:
