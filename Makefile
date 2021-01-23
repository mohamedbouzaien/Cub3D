# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/12 23:24:12 by mbouzaie          #+#    #+#              #
#    Updated: 2021/01/23 15:12:41 by mbouzaie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CUB3D_H			= -I includes/
LIBFT_H			= -I $(LIB_DIR)includes/
LIBFT_A			= libft.a

OBJ_DIR			= objs/
SRC_DIR			= srcs/
LIB_DIR			= srcs/libft/
MLX_DIR			= mlx/
LIBS_DIR		= -L. -L$(LIB_DIR) -L$(MLX_DIR)


SRCS			= main.c camera_moves.c graphical_engine.c \
					hook_events.c textures.c map_parsing.c \
					utils.c sprite.c bmp.c adapted_lst.c \
					params_parsing.c check_map_lines.c
CFIND			= $(SRCS:%=$(SRC_DIR)%)
OFILE			= $(SRCS:%.c=%.o)
OBJS			= $(addprefix $(OBJ_DIR), $(OFILE))



CC				= gcc
RM				= rm -f
CFLAGS			= -g -o #-fsanitize=address -O3 -Wall -Wextra -Werror#
				 
LIBS			= $(CUB3D_H) $(LIBFT_H) -Lmlx -lmlx -framework OpenGL -framework AppKit -lm #-lXext -lX11 -lm -lbsds
MLX				= libmlx.a

NAME			= libcub3d.a
GAME_NAME		= cub3D


all:			$(OBJ_DIR) $(GAME_NAME)

$(OBJ_DIR):
				@mkdir -p $(OBJ_DIR)

$(GAME_NAME) : $(NAME)
				@$(CC) $(CFLAGS) $(GAME_NAME) $(LIBS_DIR) -lcub3d $(LIBS)

$(NAME):		$(MLX) $(OBJS)
				@make -C $(LIB_DIR) bonus
				@cp $(LIB_DIR)$(LIBFT_A) .
				@mv $(LIBFT_A) $(NAME)
				@ar rc $(NAME) $(addprefix $(OBJ_DIR), $(OFILE))
				@ranlib $(NAME)

$(MLX):
				@make -C mlx
				@mv mlx/$(MLX) .

$(OBJS): $(CFIND)
			@make $(OFILE)

$(OFILE):
			@$(CC) $(LIBS) -c $(CFLAGS) $(OBJ_DIR)$@ $(SRC_DIR)$(@:%.o=%.c)

clean:
				@make -C mlx clean
				@/bin/rm -rf $(OBJ_DIR)
				@make -C $(LIB_DIR) clean
				@echo object files cleaned

fclean:			clean
				$(RM) $(NAME) $(MLX) $(GAME_NAME)
				@make -C $(LIB_DIR) fclean
				@echo cleaned $(NAME) and object files

re:				fclean all

.PHONY:			all clean fclean re