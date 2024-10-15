/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u.h                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 01:49:34 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/15 04:04:19 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef U_H
# define U_H

# include <stdlib.h> // size_t
# include <unistd.h> // write, read, open ... etc

# ifdef U_IMPL
#  define UALLOC_IMPL
# endif // U_IMPL

# include "ualloc.h"

# ifdef U_IMPL
#  include "u0.h"
#  include "u1.h"
#  include "u2.h"
#  include "u3.h"
#  include "u4.h"
#  include "u5.h"
# endif // U_IMPL

// u0
size_t	_strlen(const char *s);
int		_strcmp(const char *s1, const char *s2);
char	*_strchr(const char *s, const int c);
char	*_stpncpy(char *d, const char *s, size_t n);
void	*_memset(void *s, const int c, size_t n);
// u1
char	*_strdup(const char *s);
char	*_strndup(const char *s, const size_t n);
int		_strspn(const char *s, const char *a);
int		_strcspn(const char *s, const char *r);
int		_atoi(const char *s);
// u2
int		_wc(const char *s, const char *d);
char	**_split(const char *s, const char *d);
void	_splitfree(char **s);
void	_putsfd(const int fd, const char *s);
void	_putsnfd(const int fd, const char *s, size_t n);
// u3
size_t	_strnlen(const char *s, size_t n);
size_t	_strlcpy(char *d, const char *s, size_t n);
size_t	_strlcat(char *d, const char *s, size_t n);
void	*_mempcpy(void *d, const void *s, size_t n);
// u4
char	*_strapnd(const char *d, const char *s);
char	*_readline_fd(const int fd);
void	_putifd(int fd, int i);
size_t	_snprintf(char *b, size_t n, const char *f, ...);
void	_printffd(const int fd, const char *f, ...);
// u5
t_darr	_darr_new(void);
void	_darr_put(t_darr *darr, void *ptr);
void	_darr_free(t_darr *darr);

#endif // U_H
