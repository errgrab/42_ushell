/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:04:06 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/22 18:56:46 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

size_t	_strnlen(const char *s, size_t n);
size_t	_strlcpy(char *d, const char *s, size_t n);
size_t	_strlcat(char *d, const char *s, size_t n);
void	*_mempcpy(void *d, const void *s, size_t n);
char	*_strjoin(char *d, const char *s);

size_t	_strnlen(const char *s, size_t n)
{
	const char	*p = s;
	size_t		len;

	len = n;
	if (!len--)
		return (0);
	while (*p && len && len--)
		p++;
	if (*p == '\0')
		return (p - s);
	else
		return (n);
}

size_t	_strlcpy(char *d, const char *s, size_t n)
{
	char *const	d0 = d;

	if (!n--)
		return (_strlen(s));
	while (*s && n && n--)
		*d++ = *s++;
	*d = '\0';
	return (d - d0 + _strlen(s));
}

size_t	_strlcat(char *d, const char *s, size_t n)
{
	const size_t	l = _strnlen(d, n);

	if (l == n)
		return (l + _strlen(s));
	return (l + _strlcpy(d + l, s, n - l));
}

void	*_mempcpy(void *d, const void *s, size_t n)
{
	if (!d || !s)
		return (NULL);
	while (n--)
		*(char *)d++ = *(char *)s++;
	return (d);
}

char	*_strjoin(char *d, const char *s)
{
	const int	len = _strlen(d) + _strlen(s) + 1;
	char *const	res = _calloc(len, sizeof(char));

	if (!res)
		return (NULL);
	_strlcat(res, d, len);
	_strlcat(res, s, len);
	free(d);
	return (res);
}
