# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 18:38:37 by mfrasson          #+#    #+#              #
#    Updated: 2022/02/13 22:36:42 by ebresser         ###   ########.fr        #
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
			source/export.c \
			source/linked_lists.c \
			source/minishell.c \
			source/operators.c \
			source/pwd.c \
			source/read_line_and_prompt.c \
			source/separete_per_pipes.c \
			source/tokenizer.c \
			source/unset.c \
			source/utils.c \
			source/variables_I.c \
			source/variables_II.c \
			source/history.c \
			source/init_minishell.c \
			source/exit_minishell.c

OBJ		=	${SRC:.c=.o}

INCD	=	includes/minishell.h

NAME	=	minishell

MODULE	=	./libft/libft.a

FLAGS	=	-Wall -Wextra -Werror -lreadline -lncurses

DEBUG	=	-g -fsanitize=address

RM		=	rm -rf

.c.o:
	@${CC} -fPIC ${FLAGS} -c $< -o ${<:.c=.o}

all:			$(NAME)

$(NAME):	$(MODULE) $(OBJ) $(INCD)
	$(CC) -fPIC $(OBJ) $(FLAGS) $(MODULE) -o $(NAME)

debug: $(OBJ) $(MODULE)
	$(CC) -fPIC $(OBJ) $(FLAGS) $(MODULE) $(DEBUG) -o $(NAME)


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
