# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/05 12:40:00 by mfrasson          #+#    #+#              #
#    Updated: 2021/06/05 00:23:28 by mfrasson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	= $(wildcard $(DIR_SRCS)*.c)


CC=clang
HEADER=libft.h
INCLUDES= libft.h
NAME=libft.a
FLAGS = -Wall -Wextra -Werror
OBJS=$(SRC:.c=.o)
OBJS_BONUS=$(BNS:.c=.o)


all:	$(NAME)

$(NAME):
	@clang $(FLAGS) -I $(HEADER) -c $(SRC)
	@ar rcs $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)
	@rm -f $(OBJS_BONUS)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all