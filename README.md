# minishell

Minishell is a small command-line interpreter written in C. It allows users to execute commands and navigate the file system using a subset of the features available in a full shell.

## Building minishell

To build minishell, you will need a C compiler and the `make` utility.

1. Clone the repository: `git clone https://github.com/marceFrasson/minishell.git`
2. Change into the project directory: `cd minishell`
3. Build the project: `make`

This will create a `minishell` executable in the project directory.

## Running minishell

To start minishell, simply run the `minishell` executable:

```shell
./minishell
```

This will start the minishell interpreter and display a prompt. You can then enter commands to be executed.

## Features

Minishell supports the following features:

- Executing external commands and programs, such as `ls`, `wc`, and others
- Built-in commands for changing the current working directory (`cd`), setting and displaying environment variables (`setenv`, `unsetenv`, and `env`), and exiting the shell (`exit`)
- Pipes and redirections (with a limited implementation)

Minishell does not support all of the features of a full shell, such as background processes and more advanced forms of pipes and redirections.

## References

Minishell was developed as a project for the 42 São Paulo curriculum. The `ft_printf` and `libft` directories contain custom implementations of the `printf` function and a library of utility functions, respectively, which were required as part of the project. These directories are not directly related to the minishell interpreter.
