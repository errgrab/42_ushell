/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 01:49:34 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/16 23:23:05 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef U_H
# define U_H

# include <stdlib.h> // size_t
# include <unistd.h> // write, read, open ... etc
# include "ualloc.h"

typedef struct s_darr	t_darr;
struct s_darr
{
	size_t	cap;
	size_t	len;
	void	**data;
};

// lib0
size_t	_strlen(const char *s);
int		_strcmp(const char *s1, const char *s2);
char	*_strchr(const char *s, const int c);
char	*_stpncpy(char *d, const char *s, size_t n);
void	*_memset(void *s, const int c, size_t n);
// lib1
char	*_strdup(const char *s);
char	*_strndup(const char *s, const size_t n);
int		_strspn(const char *s, const char *a);
int		_strcspn(const char *s, const char *r);
int		_atoi(const char *s);
// lib2
int		_wc(const char *s, const char *d);
char	**_split(const char *s, const char *d);
void	_splitfree(char **s);
void	_putsfd(const int fd, const char *s);
void	_putsnfd(const int fd, const char *s, size_t n);
// lib3
size_t	_strnlen(const char *s, size_t n);
size_t	_strlcpy(char *d, const char *s, size_t n);
size_t	_strlcat(char *d, const char *s, size_t n);
void	*_mempcpy(void *d, const void *s, size_t n);
// lib4
char	*_strapnd(const char *d, const char *s);
char	*_readline_fd(const int fd);
void	_putifd(int fd, int i);
size_t	_snprintf(char *b, size_t n, const char *f, ...);
void	_printffd(const int fd, const char *f, ...);
// lib5
t_darr	_darr_new(void);
void	_darr_put(t_darr *darr, void *ptr);
void	_darr_free(t_darr *darr);

#endif // U_H