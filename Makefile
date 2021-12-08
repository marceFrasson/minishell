# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itaureli <itaureli@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 18:38:37 by mfrasson          #+#    #+#              #
#    Updated: 2021/12/08 06:21:34 by itaureli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	source/reading_line.c source/exec.c

OBJ		=	${SRC:.c=.o}

INCD	=	includes/minishell.h

NAME	=	minishell

MODULE	=	./libft/libft.a

CFLAGS	=	-Wall -Wextra -Werror -lreadline

RM		=	rm -rf

CC		=	clang

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

all:			$(NAME)

$(NAME):	$(MODULE) $(OBJ) $(INCD)
	$(CC) $(CFLAGS) $(OBJ) $(MODULE) -o $(NAME)
$(MODULE):
	make -C libft
	@echo ""
	@echo "|		minishell created		|"
	@echo ""

clean:
	$(RM) $(OBJ)
	make clean -C libft
	@echo ""
	@echo "|		minishell deleted		|"
	@echo ""

fclean:		clean
	$(RM) $(NAME)
	make fclean -C libft

re:			fclean all

git:
	git add .
	git status
	git commit -m "$m"

.PHONY:		all clean fclean re git
