NAME = cub3D

CC = gcc

CFLAGS = -I minilibx -L minilibx_macos -lmlx -framework OpenGL -framework AppKit

RM = rm -rf

SRCS = 	src/*.c\
		src/parsing/*.c\
        libft/libft.a\

SRCS_BONUS = src_bonus/*.c\
        libft/libft.a\

$(NAME) :
	make all -C minilibx_macos
	make all -C libft
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

bonus :
	make clean
	make all -C minilibx_macos
	make all -C libft
	gcc $(CFLAGS) $(SRCS_BONUS) -o $(NAME)

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