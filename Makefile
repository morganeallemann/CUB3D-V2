# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: malleman <malleman@42lausanne.ch>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/07 13:39:48 by malleman          #+#    #+#              #
#    Updated: 2023/02/15 17:05:37 by malleman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#--------------------------	SOURCES -------------------------------------------#
SRCS_PATH	=	./sources/

SRCS		= 	main.c \
				parsing/check_textures.c parsing/checker_map.c \
				parsing/create_map.c parsing/get_map_info.c \
				parsing/get_tex_color.c parsing/parse_map.c parsing/parsing.c \
				init/init_player_dir.c init/init_struct.c init/init_textures.c \
				init/init_mlx.c \
				exit/errors.c exit/exit.c exit/free.c \

SRC_DIR 	= 	$(addprefix sources/, $(SRCS))
#--------------------------	VARIABLES -----------------------------------------#
NAME		= cub3D

OBJS		= ${SRC_DIR:.c=.o}

INCLUDES 	= -Iincludes/

LIBFT 		= libft/libft.a mlx_mac/libmlx.dylib

CC			= gcc
CFLAGSDDBUG	= -Wall -Wextra -Werror -g 
CFLAGS		= -Wall -Wextra -Werror

RM			= rm -rf

#-------------------------- COMMANDES -----------------------------------------#
%.o: %.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

all: 	${NAME}

${LIBFT}:
	cd mlx/ && make && cp libmlx.a ../
	cd libft/ && make

$(NAME): ${LIBFT} $(OBJS)
	$(CC) ${CFLAGS} $(OBJS) -L./libft -L. -lmlx -lm -lft -framework OpenGL -framework AppKit -o $(NAME)

clean:
	cd libft/ && make clean
	cd mlx/ && make clean
	${RM} ${OBJS}

fclean: clean
	cd libft/ && make fclean
	${RM} ${NAME}
	${RM} ${LIBFT}
	$(RM) libmlx.dylib

re: 	fclean all

.PHONY: all clean fclean re