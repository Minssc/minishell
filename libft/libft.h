/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 13:00:40 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:23:39 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}				t_dlist;

typedef struct s_que
{
	t_dlist		*head;
	t_dlist		*tail;
	int			size;
}				t_que;

typedef struct s_dque
{
	t_dlist		*head;
	t_dlist		*tail;
	int			size;
}				t_dque;

void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
size_t			ft_strlcat(char *dest, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
long long		ft_atol(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);

void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *str);

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putstrn_fd(char *s, int fd, size_t len);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));

t_dlist			*ft_dlstnew(void *content);
t_dlist			*ft_dlstlast(t_dlist *lst);
t_dlist			*ft_dlstfirst(t_dlist *lst);
void			ft_dlstadd_front(t_dlist **lst, t_dlist *new);
void			ft_dlstadd_back(t_dlist **lst, t_dlist *new);
void			ft_dlstins_front(t_dlist **lst, t_dlist *new);
void			ft_dlstins_back(t_dlist **lst, t_dlist *new);
int				ft_dlstsize(t_dlist *lst);
void			ft_dlstdelone(t_dlist *lst, void (*del)(void *));
void			ft_dlstclear(t_dlist **lst, void (*del)(void *));
void			ft_dlstiter(t_dlist *lst, void (*f)(void *));
t_dlist			*ft_dlstmap(t_dlist *lst, void *(*f)(void *),
					void (*del)(void *));
int				get_next_line(int fd, char **line);
void			get_next_line_clear(void);

int				ft_maxi(int a, int b);
size_t			ft_maxs(size_t a, size_t b);
long long		ft_maxll(long long a, long long b);
float			ft_maxf(float a, float b);
double			ft_maxd(double a, double b);

int				ft_mini(int a, int b);
size_t			ft_mins(size_t a, size_t b);
long long		ft_minll(long long a, long long b);
float			ft_minf(float a, float b);
double			ft_maxd(double a, double b);

int				ft_absi(int v);
long long		ft_absl(long long v);
float			ft_absf(float v);
double			ft_absd(double v);

int				ft_isnumstr(char *str);

void			ft_qpush(t_que *q, void *v);
void			ft_qpop(t_que *q);
void			*ft_qtop(t_que *q);
int				ft_qempty(t_que *q);
int				ft_qsize(t_que *q);
void			ft_qclear(t_que *q, void (*del)(void *));

#endif
