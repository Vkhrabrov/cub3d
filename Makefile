# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkhrabro <vkhrabro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 21:20:12 by ccarrace          #+#    #+#              #
#    Updated: 2024/05/28 22:19:33 by vkhrabro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Variables -------------------------------------------------------------- #

CC				=		gcc
HEADER_NAME		=		cub3d.h
LIBMLX_NAME		=		libmlx_Linux.a
LIBFT_NAME		=		libft.a
NAME			=		cub3d

# --- Compiler flags --------------------------------------------------------- #

CFLAGS			=		-MMD -Wall -Wextra -Werror
LIBMLX_FLAGS	=		-lmlx -lX11 -lXext -lm -lbsd

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
SRC_FILES		=		main.c

# --- Files full paths ------------------------------------------------------- #

LIBFT_PATH		= 		$(addprefix $(LIBFT_DIR), $(LIBFT_NAME))
LIBMLX_PATH		= 		$(addprefix $(LIBMLX_DIR), $(LIBMLX_NAME))
OBJ_PATH		=		$(addprefix $(OBJ_DIR), $(OBJ_FILES))
DEP_PATH		=		$(addprefix $(DEP_DIR), $(DEP_FILES))

# --- Compilation rules ------------------------------------------------------ #

all:
		mkdir -p $(OBJ_DIR)
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
			rm -rf $(OBJ_DIR)
			$(MAKE) -C $(LIBFT_DIR) clean
			$(MAKE) -C $(LIBMLX_DIR) clean

fclean:		clean
			rm -f $(NAME)
			$(MAKE) -C $(LIBFT_DIR) fclean
			$(MAKE) -C $(LIBMLX_DIR) clean

re:			fclean all

.PHONY:		all clean fclean re

