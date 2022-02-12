# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/05 12:40:00 by mfrasson          #+#    #+#              #
#    Updated: 2022/02/12 14:11:08 by ebresser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	= $(wildcard $(DIR_SRCS)*.c)


CC=clang
HEADER=libft.h
INCLUDES= libft.h
NAME=libft.a
FLAGS = -Wall -Wextra -Werror
OBJS=$(SRC:.c=.o)


all:	$(NAME)

$(NAME):
	@clang -fPIC $(FLAGS) -I $(HEADER) -c $(SRC)
	@ar rcs $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all