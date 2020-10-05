# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbouzaie <mbouzaie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/03 15:10:22 by mbouzaie          #+#    #+#              #
#    Updated: 2020/05/12 19:12:27 by mbouzaie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = libft.a

HEADER = includes/

FLAGS = -Wall -Wextra -Werror -g

OPTION = -I $(HEADER) -c

SRC = 	ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isupper.c \
		ft_islower.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_isspace.c \
		ft_isblank.c \
		ft_strupr.c \
		ft_strdup.c \
		ft_calloc.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strnew.c \
		ft_strcpy.c \
		ft_strcat.c \
		ft_memalloc.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_intlen.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strnjoin.c \
		ft_chrloc.c  \
		ft_memdel.c \
		ft_uitoa.c \

SRC_B =	ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \

OBJ = ${SRC:.c=.o}

OBJ_B =	${SRC_B:.c=.o}
		
all: $(NAME)

$(NAME):
	$(CC) $(FLAGS) $(OPTION) $(SRC)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	@echo "libft est la\n"

bonus: $(OBJ) $(OBJ_B)
	ar rcs $(NAME) $(OBJ) $(OBJ_B)
	@echo "libft bonus est la\n"	

clean:
	/bin/rm -f $(OBJ) $(OBJ_B)
	@echo "Les fichier .o sont efface"

fclean: clean
	/bin/rm -f $(NAME)
	@echo "$(NAME) ainsi que les fichiers .o sont efface"

re: fclean all

.PHONY: all re fclean clean