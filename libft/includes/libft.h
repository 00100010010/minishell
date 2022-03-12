/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 16:18:54 by jim               #+#    #+#             */
/*   Updated: 2021/05/25 10:34:39 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# define BUFFER_SIZE 30
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void				ft_free_array(char **array);
int					get_next_line(int fd, char **line);
char				ft_isascii(int c);
char				ft_isdigit(int c);
char				ft_isspace(int c);
char				ft_isalnum(int c);
char				ft_isprint(int c);
char				*ft_itoa(long long n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *hk, const char *ne, size_t len);
char				*ft_strdup(const char *s1);
char				**ft_array_dup(char **array);
int					ft_array_strncmp(char **array, char *str, size_t n);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin_char(char const *s1, char c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strtrim_pos(char *line, int start, int end);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				**ft_split(char const *s, char c);
char				**ft_split_custom(char *s,
						int (*valid_state)(char *, int, int));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr(char *s);
void				ft_putstr_fd(char *s, int fd);
void				ft_put_array(char **array, char *separator, int sepa_flag);
void				ft_put_array_fd(char **array, char *separator,
						int sepa_flag, int fd);
char				**ft_array_addstr(char **array, char *newstr);
char				**ft_array_delstr(char **array, char *delstr);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_bzero(void *s, size_t n);
void				*ft_bzero_ptr(void *b, size_t len);
void				ft_malloc_error_exit(char *message);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_int_size(int nbr);
int					ft_isalpha(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
long long			ft_atoi(const char *s);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlen(register const char *str);
size_t				ft_array_len(char **array);
char				**ft_array_replace_str_chr(char **array,
						char *to_replace, char *newstr);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
void				ft_put_color_fd(char *id, int fd);
#endif
