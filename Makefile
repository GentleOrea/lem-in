#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 11:17:30 by ygarrot           #+#    #+#              #
#    Updated: 2018/02/28 13:40:23 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in 

SRC = browse_list.c main.c resolve.c init.c erase.c parser.c \
	  print_paths.c set_value.c

INCLUDE =  includes/

FLAGS = -Wall -Werror -Wall

LIBFT = libft/libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@gcc -o $@ $(FLAGS) -c $<

$(LIBFT):
	@make -C libft

$(NAME): $(LIBFT) $(OBJ)
	 @gcc -o $(NAME) $^ -I $(INCLUDE)

test: all clean

clean:
	@rm -f $(OBJ)
	@make -C libft clean
	
fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all

.PHONY: all, clean, fclean, re,
