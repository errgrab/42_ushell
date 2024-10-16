/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib0.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 01:35:13 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/16 23:37:16 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

size_t	_strlen(const char *s);
int		_strcmp(const char *s1, const char *s2);
char	*_strchr(const char *s, const int c);
char	*_stpncpy(char *d, const char *s, size_t n);
void	*_memset(void *s, const int c, size_t n);

size_t	_strlen(const char *s)
{
	size_t	l;

	if (!s)
		return (0);
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

char	*_strchr(const char *s, const int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((void *)s);
	return (NULL);
}

char	*_stpncpy(char *d, const char *s, size_t n)
{
	while (*s && n && n--)
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
