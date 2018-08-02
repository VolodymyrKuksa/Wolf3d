# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/06 11:20:53 by vkuksa            #+#    #+#              #
#    Updated: 2018/03/06 11:20:55 by vkuksa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

LFT = $(LFT_DIR)libft.a

SRC_DIR = ./src/
OBJ_DIR	= ./obj/
INC_DIR = ./includes/
LFT_DIR = ./libft/
LFT_INC_DIR = $(LFT_DIR)includes/
MLX_DIR = ./minilibx/

LMX = -lmlx -L $(MLX_DIR) -framework OpenGL -framework AppKit
CC = gcc
CC_FLAGS = -c -Wall -Werror -Wextra
INC = -I $(INC_DIR) -I $(LFT_INC_DIR) -I $(MLX_DIR)

C_FILES =	collisions.c\
			draw_line.c\
			gradient.c\
			image_utils.c\
			input.c\
			input_utils.c\
			load_sprites.c\
			load_textures.c\
			main.c\
			map_utils.c\
			menues.c\
			minimap.c\
			output.c\
			read_map.c\
			render.c\
			render_sprites.c\
			render_utils.c\
			secret_walls.c\
			update.c\
			utils.c\
			wall_texturing.c\

SRC = $(addprefix $(SRC_DIR), $(C_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(C_FILES:.c=.o))

all: $(NAME)

$(NAME): $(LFT) $(OBJ_DIR) $(OBJ)
	make -C $(MLX_DIR)
	$(CC) $(OBJ) $(LFT) $(LMX) -o $(NAME)

$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	$(CC) $(CC_FLAGS) $(INC) $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LFT):
	make -C $(LFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LFT_DIR) clean
	make -C $(MLX_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LFT_DIR) fclean

re: fclean all
