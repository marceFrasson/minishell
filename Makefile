# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 18:38:37 by mfrasson          #+#    #+#              #
#    Updated: 2022/02/08 21:14:45 by mfrasson         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	source/cd.c \
			source/check_syntax.c \
			source/comments.c \
			source/debugger.c \
			source/echo.c \
			source/env.c \
			source/envp.c \
			source/exit.c \
			source/linked_lists.c \
			source/minishell.c \
			source/pwd.c \
			source/read_line_and_prompt.c \
			source/separete_per_pipes.c \
			source/tokenizer.c \
			source/unset.c \
			source/utils.c \
			source/variables.c

OBJ		=	${SRC:.c=.o}

INCD	=	includes/minishell.h

NAME	=	minishell

MODULE	=	./libft/libft.a

CFLAGS	=	-Wall -Wextra -Werror 

FLAGS	=	-Wall -Wextra -Werror -lreadline -lncurses

RM		=	rm -rf

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

all:			$(NAME)

$(NAME):	$(MODULE) $(OBJ) $(INCD)
	$(CC) $(OBJ) $(FLAGS) $(MODULE) -o $(NAME)
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

install:
	@sudo apt-get -y install libreadline-dev

re:			fclean all

git:
	git add .
	git status
	git commit -m "$m"

.PHONY:		all clean fclean re git
