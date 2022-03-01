/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrasson <mfrasson@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 14:22:35 by mfrasson          #+#    #+#             */
/*   Updated: 2022/02/07 22:02:30 by mfrasson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/resource.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

typedef struct s_list
{
	struct s_list	*prev;
	void			*vol;
	struct s_list	*next;
}					t_list;

/*
** part 1
*/

double		ft_atod(const char *str);
int			ft_atoi(const char *str);
void		ft_bzero(void *str, size_t size);
void		*ft_calloc(size_t str, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(char c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_splitlen(char **str);
void		*ft_memccpy(void *dst, const void *src, int c, size_t size);
void		*ft_memchr(const void *str, int c, size_t size);
int			ft_memcmp(const void *str1, const void *str2, size_t size);
void		*ft_memcpy(void *dst, const void *src, size_t size);
void		*ft_memmove(void *str1, const void *str2, size_t size);
void		*ft_memset(void *str, int c, size_t size);
char		*ft_charjoin(char const *string1, char const c);
char		*ft_strchr(const char *str, int c);
char		*ft_strdup(const char *str);
char    	*ft_strcopy(char *src, char *dst);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_strlen(const char *str);
int			ft_strcmp(const char *string1, const char *string2);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
char		*ft_strnstr(const char *src, const char *to_find, size_t n);
char		*ft_strrchr(const char *str, int c);
int			ft_tolower(int c);
int			ft_toupper(int c);

/*
** part 2
*/

double		ft_atod(const char *str);
char		*ft_itoa(int n);
void		ft_putchar(char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *str, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr(char *str);
void		ft_putstr_fd(char *str, int fd);
char		**ft_split(char const *str, char c);
char		*ft_strjoin(char const *prefix, char const *suffix);
char		*ft_strmapi(char const *str, char (*f)(unsigned int, char));
char		*ft_strtrim(char const *str, char const *ref);
char		*ft_substr(char const *string, unsigned int start, size_t len);

int			get_next_line(int fd, char **line);

void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstloop_start(t_list **lst);
void		ft_lstloop_stop(t_list **lst);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);

void		ft_free_split(char **str);

#endif
