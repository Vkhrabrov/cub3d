# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 21:20:12 by ccarrace          #+#    #+#              #
#    Updated: 2024/07/07 14:24:13 by ccarrace         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Variables -------------------------------------------------------------- #

CC				=		gcc
HEADER_NAME		=		cub3d.h
LIBMLX_NAME		=		libmlx.a
LIBFT_NAME		=		libft.a
NAME			=		cub3D

# --- Compiler flags --------------------------------------------------------- #

CFLAGS			=		-MMD -Wall -Wextra -Werror -g #-fsanitize=address 
#LIBMLX_FLAGS	=		-lmlx -framework OpenGL -framework AppKit
LIBMLX_FLAGS 	=		-lmlx -lX11 -lXext -lm -lbsd

# --- Directories ------------------------------------------------------------ #

LIBMLX_DIR		=		libraries/minilibx_linux/
LIBFT_DIR		=		libraries/libft/
INC_DIR			=		includes/
SRC_DIR			=		sources/
OBJ_DIR			=		objects/
DEP_DIR			= 		$(OBJ_DIR)

# --- Includes --------------------------------------------------------------- #

INCLUDES		=		-I $(INC_DIR) -I $(LIBFT_DIR) -I $(LIBMLX_DIR)
LIB_INCLUDE		=		-L $(LIBFT_DIR) -lft -L $(LIBMLX_DIR) $(LIBMLX_FLAGS)

# --- Files ------------------------------------------------------------------ #

OBJ_FILES 		= 		$(SRC_FILES:.c=.o)
DEP_FILES 		= 		$(SRC_FILES:.c=.d)
SRC_FILES		=		main.c \
						init/init.c \
						engine.c \
						parse/check_file.c \
						parse/find_map_dimensions.c \
						parse/check_scene_description.c \
						parse/check_scene_description2.c \
						parse/check_textures.c \
						parse/check_textures2.c \
						parse/check_colors.c \
						parse/check_player.c \
						parse/create_arrays.c \
						parse/create_arrays2.c \
						parse/check_walls.c \
						parse/check_walls2.c \
						parse/parse_utils.c \
						parse/parse_utils2.c \
						parse/parse_utils3.c \
						parse/reading_utils.c \
						debug.c

# --- Files full paths ------------------------------------------------------- #

LIBFT_PATH		= 		$(addprefix $(LIBFT_DIR), $(LIBFT_NAME))
LIBMLX_PATH		= 		$(addprefix $(LIBMLX_DIR), $(LIBMLX_NAME))
OBJ_PATH		=		$(addprefix $(OBJ_DIR), $(OBJ_FILES))
DEP_PATH		=		$(addprefix $(DEP_DIR), $(DEP_FILES))

# --- Compilation rules ------------------------------------------------------ #

all:
		mkdir -p $(OBJ_DIR) $(OBJ_DIR)/parse $(OBJ_DIR)/init
		$(MAKE) -C $(LIBFT_DIR)
		$(MAKE) -C $(LIBMLX_DIR)
		$(MAKE) $(NAME)

$(NAME): $(OBJ_PATH) $(LIBMLX_PATH) Makefile
	$(CC) $(CFLAGS)  $(INCLUDES) $(OBJ_PATH) -o $@ $(LIB_INCLUDE)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -c $< -o $@

-include $(DEP_PATH)

# --- Cleaning rules --------------------------------------------------------- #

clean:	
			rm -f $(OBJ_PATH) $(DEP_PATH)
			rm -rf $(OBJ_DIR)c
			$(MAKE) -C $(LIBFT_DIR) clean
			$(MAKE) -C $(LIBMLX_DIR) clean

fclean:		clean
			rm -f $(NAME)
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(MAKE) -C $(LIBMLX_DIR) clean

re:			fclean all

.PHONY:		all clean fclean re
