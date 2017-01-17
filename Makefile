# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahunt <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/30 15:41:53 by ahunt             #+#    #+#              #
#    Updated: 2016/11/30 15:41:58 by ahunt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1

CC = gcc

INC += include libft/include

LIBFT = ./libft/libft.a

LIBFT_LINK = -L libft -lft

MLX = ./minilibx_macos/libmlx.a

MLX_LINK = -L minilibx_macos -lmlx

CFLAGS += $(foreach d, $(INC), -I$d)

FRMWRK = -framework OpenGL -framework AppKit

AR = ar

RLIB = ranlib

RM = rm -rf

SRC_BASE = 	main.c \
			init_mlx.c \
			draw.c \

SRC = $(addprefix src/, $(SRC_BASE))

OBJ = $(addprefix obj/, $(SRC_BASE:.c=.o))

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(OBJ): | obj

obj:
	mkdir -p $@
	mkdir -p $@/color_mapping

obj/color_mapping/%.o: src/color_mapping/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) -o $@ $^  $(CFLAGS) -L libft -lft -L minilibx_macos -lmlx -framework OpenGL -framework AppKit

debug: $(OBJ)
	$(CC) -fsanitize=address  -o $@ $^  $(CFLAGS) -L libft -lft -L minilibx_macos -lmlx -framework OpenGL -framework AppKit

clean:
	$(RM) $(OBJ)
	make -C ./libft clean

fdf_clean:
	$(RM) $(OBJ)

fclean: fdf_clean
	$(RM) $(NAME)
	$(RM) obj
	make -C ./libft fclean

fdf_fclean: fdf_clean
	$(RM) $(NAME)
	$(RM) obj

re: fdf_fclean all
	make -C ./libft re

.PHONY: all clean fclean re
