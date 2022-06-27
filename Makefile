# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lxu-wu <lxu-wu@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/27 14:05:14 by lxu-wu            #+#    #+#              #
#    Updated: 2022/06/27 14:19:25 by lxu-wu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc

CFLAGS = -Werror -Wextra -Wall -I minilibx -L minilibx_macos -lmlx -framework OpenGL -framework AppKit

RM = rm -rf

SRCS = 	src/dlst.c\
		src/draw.c\
		src/free.c\
		src/init.c\
		src/keys.c\
		src/main.c\
	    src/raycaster.c\
		src/raycaster2.c\
		src/split1.c\
		src/up_param.c\
		src/utils.c\
		src/utils2.c\
		src/utils3.c\
		src/parsing/check_map.c\
		src/parsing/colors.c\
		src/parsing/cp_map.c\
		src/parsing/map_elem.c\
		src/parsing/parsing.c\
		src/parsing/parsing_utils.c\
		src/parsing/parsing_utils2.c\
		src/parsing/read_file.c

SRCS_BONUS = src_bonus/dlst_bonus.c\
		src_bonus/minimap_bonus.c\
		src_bonus/sprites_bonus.c\
		src_bonus/draw_bonus.c\
		src_bonus/free_bonus.c\
		src_bonus/init_bonus.c\
		src_bonus/keys_bonus.c\
		src_bonus/main_bonus.c\
	    src_bonus/raycaster_bonus.c\
		src_bonus/raycaster2_bonus.c\
		src_bonus/split1_bonus.c\
		src_bonus/up_param_bonus.c\
		src_bonus/utils_bonus.c\
		src_bonus/utils2_bonus.c\
		src_bonus/utils3_bonus.c\
		src_bonus/parsing/check_map_bonus.c\
		src_bonus/parsing/colors_bonus.c\
		src_bonus/parsing/cp_map_bonus.c\
		src_bonus/parsing/map_elem_bonus.c\
		src_bonus/parsing/parsing_bonus.c\
		src_bonus/parsing/parsing_utils_bonus.c\
		src_bonus/parsing/parsing_utils2_bonus.c\
		src_bonus/parsing/read_file_bonus.c


$(NAME) : ${SRCS}
	make all -C minilibx_macos
	make bonus -C libft
	gcc $(CFLAGS) $(SRCS) libft/libft.a -o $(NAME)

bonus : ${SRCS_BONUS}
	make clean
	make all -C minilibx_macos
	make bonus -C libft
	gcc $(CFLAGS) $(SRCS_BONUS) libft/libft.a -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make clean -C minilibx_macos
	make fclean -C libft

clean :
	$(RM) $(NAME)
	make clean -C minilibx_macos
	make clean -C libft

re : fclean all
