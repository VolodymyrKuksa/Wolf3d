# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/26 11:01:38 by vkuksa            #+#    #+#              #
#    Updated: 2018/01/11 14:23:37 by vkuksa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ./ft_atoi.c ./ft_bzero.c ./ft_isalnum.c ./ft_isalpha.c ./ft_isascii.c \
./ft_isdigit.c ./ft_isprint.c ./ft_itoa.c ./ft_lstadd.c ./ft_lstdel.c \
 ./ft_lstdelone.c ./ft_lstiter.c ./ft_lstmap.c ./ft_lstnew.c ./ft_memalloc.c \
./ft_memccpy.c ./ft_memchr.c ./ft_memcmp.c ./ft_memcpy.c ./ft_memdel.c \
./ft_memmove.c ./ft_memset.c ./ft_putchar.c ./ft_putchar_fd.c ./ft_putendl.c \
./ft_putendl_fd.c ./ft_putnbr.c ./ft_putnbr_fd.c ./ft_putstr.c \
./ft_putstr_fd.c ./ft_strcat.c ./ft_strchr.c ./ft_strclr.c ./ft_strcmp.c \
./ft_strcpy.c ./ft_strdel.c ./ft_strdup.c ./ft_strequ.c ./ft_striter.c \
./ft_striteri.c ./ft_strjoin.c ./ft_strlcat.c ./ft_strlen.c ./ft_strmap.c \
./ft_strmapi.c ./ft_strncat.c ./ft_strncmp.c ./ft_strncpy.c ./ft_strnequ.c \
./ft_strnew.c ./ft_strnstr.c ./ft_strrchr.c ./ft_strsplit.c ./ft_strstr.c \
./ft_strsub.c ./ft_strtrim.c ./ft_tolower.c ./ft_toupper.c ./ft_brainfuck.c \
./ft_swap.c ./ft_sort_int_tab.c ./ft_sort_str_tab.c ./ft_atoi_base.c \
./ft_itoa_base.c ft_mat_mult.c get_next_line.c ft_new_matrix.c \
ft_mat_scalar_mult.c ft_mat_scalar_div.c ft_mat_scalar_add.c \
ft_clear_matrix.c
OBJ = $(SRC:.c=.o) 
CC = gcc
FLAGS = -Wall -Wextra
INC = ./libft.h

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o : %.c
	$(CC) -c -I ./includes/ $(FLAGS) $<

clean:
	/bin/rm -rf $(OBJ)

fclean: clean
	/bin/rm -rf $(NAME)

re: fclean $(NAME)
