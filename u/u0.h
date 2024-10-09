/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u0.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 01:35:13 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/09 13:19:13 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef U0_H
# define U0_H

# include "u.h"

int		_strlen(const char *s);
int		_strcmp(const char *s1, const char *s2);
void	*_strchr(const char *s, const int c);
char	*_stpcpy(char *d, const char *s);
void	*_memset(void *s, const int c, size_t n);

int	_strlen(const char *s)
{
	int	l;

	l = 0;
	while (s[l])
		l++;
	return (l);
}

int	_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2 && *s1 && *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	*_strchr(const char *s, const int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((void *)s);
	return (NULL);
}

char	*_stpcpy(char *d, const char *s)
{
	while (*s)
		*d++ = *s++;
	*d = '\0';
	return (d);
}

void	*_memset(void *s, const int c, size_t n)
{
	while (n--)
		*((char *)s + n) = (char)c;
	return (s);
}

#endif
