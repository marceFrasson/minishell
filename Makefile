# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebresser <ebresser@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 18:38:37 by mfrasson          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2022/03/02 23:41:22 by ebresser         ###   ########.fr        #
=======
#    Updated: 2022/03/02 18:34:00 by mfrasson         ###   ########.fr        #
>>>>>>> main
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
			source/export_I.c \
			source/export_II.c \
			source/linked_lists.c \
			source/minishell.c \
			source/operators.c \
			source/pwd.c \
			source/read_line_and_prompt.c \
			source/separete_per_pipes.c \
			source/tokenizer.c \
			source/tokenizer_math.c \
			source/unset.c \
			source/utils.c \
			source/variables_I.c \
			source/variables_II.c \
			source/history.c \
			source/init_minishell.c \
			source/exit_minishell.c \
			source/exec_commands.c \
			source/file_descriptors.c \
			source/free_g_struct.c \
			source/builtin_select.c \
			source/processes_handler.c

OBJ		=	${SRC:.c=.o}

INCD	=	includes/minishell.h

NAME	=	minishell

MODULE	=	./libft/libft.a

FLAGS	=	-Wall -Wextra -Werror -lreadline -lncurses -g3

DEBUG	=	-g -fsanitize=address

RM		=	rm -rf

CC		=	gcc

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
