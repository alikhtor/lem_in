# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/01 13:08:41 by alikhtor          #+#    #+#              #
#    Updated: 2018/05/30 16:49:56 by alikhtor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name of the executable file

NAME := 	libft.a

# project directories

SRC_DIR := 	./sources/
OBJ_DIR := 	./objects/
INC_DIR := 	./includes/

# project source files

SRC :=		ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
	  		ft_memmove.c ft_memchr.c ft_memcmp.c ft_memalloc.c \
	  		ft_memdel.c ft_strlen.c ft_strdup.c ft_strcpy.c \
	  		ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c \
	  		ft_strchr.c ft_strrchr.c ft_strstr.c ft_strnstr.c \
	  		ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c \
	  		ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	  		ft_toupper.c ft_tolower.c ft_strnew.c ft_strdel.c \
	  		ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c \
	  		ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
	  		ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c \
	  		ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
	  		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	  		ft_putnbr_fd.c ft_lstadd.c ft_lstdel.c \
	  		ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c \
	  		get_next_line.c

OBJ :=		$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# compilation flags

FLAGS :=	-Wall -Wextra -Werror

# header flag

H_FLAG :=	-I $(INC_DIR)

# rules

all: $(NAME)

$(NAME): $(OBJ)
	@ ar rc $(NAME) $(OBJ)
	@ ranlib $(NAME)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@ mkdir $(OBJ_DIR)
	
$(OBJ_DIR)%.o: %.c
	@ gcc -c $< -o $@ $(FLAGS) $(H_FLAG)

clean:
	@ rm -rf $(OBJ_DIR)

fclean: clean
	@ rm -f $(NAME)

re: fclean all

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re
