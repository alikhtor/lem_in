# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alikhtor <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/30 15:15:49 by alikhtor          #+#    #+#              #
#    Updated: 2018/07/04 15:25:36 by alikhtor         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name of the executable file

NAME :=				lem-in

# project directories

SRC_DIR := 			./sources/
OBJ_DIR := 			./objects/
INC_DIR := 			./includes/
LIB_DIR := 			./libftprintf/

# project source files

SRC :=				main.c

OBJ := 				$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# libraries

LIBFT := 			$(LIB_DIR)libftprintf.a
LIBFT_INC := 		$(LIB_DIR)includes/

# compilation flags

FLAGS := 			-Wall -Wextra -Werror -O3

# header flags

HEADER_FLAGS := 	-I $(INC_DIR) -I $(LIBFT_INC)

# rules

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
		@ gcc $(FLAGS) -o $(NAME) $(OBJ) $(LIBFT)
		@ printf "\e[32mCOMPILING DONE!\n"

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
		@ mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c
		@ gcc -c $< -o $@ $(FLAGS) $(HEADER_FLAGS)

$(LIBFT):
		@ make -C $(LIB_DIR)

clean:
		@ rm -rf $(OBJ_DIR)
		@ make clean -C $(LIB_DIR)
		@ printf "\e[33mCLEANING DONE\n"

fclean:
		@ rm -f $(NAME)
		@ rm -rf $(OBJ_DIR)
		@ make fclean -C $(LIB_DIR)
		@ printf "\e[31mFULL CLEANING DONE\n"

re: fclean all

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re
