/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u1.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 01:45:16 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/04 02:56:17 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef U1_H
# define U1_H

# include "u.h"

char	*_strdup(const char *s);
char	*_strndup(const char *s, const size_t n);
int		_strspn(const char *s, const char *a);
int		_strcspn(const char *s, const char *r);
int		_atoi(const char *s);

char	*_strdup(const char *s)
{
	auto char *r = _calloc(_strlen(s) + 1, sizeof(char));
	_stpcpy(r, s);
	return (r);
}

char	*_strndup(const char *s, const size_t n)
{
	auto size_t l = _strlen(s);
	if (n < l)
		l = n;
	auto char *r = _calloc(l + 1, sizeof(char));
	if (!r)
		return (NULL);
	r[l] = 0;
	while (l--)
		r[l] = s[l];
	return (r);
}

int	_strspn(const char *s, const char *a)
{
	auto int l = 0;
	while (s[l] && _strchr(a, s[l]))
		l++;
	return (l);
}

int	_strcspn(const char *s, const char *r)
{
	auto int l = 0;
	while (s[l] && !_strchr(r, s[l]))
		l++;
	return (l);
}

int	_atoi(const char *s)
{
	auto int r = 0, p = 1;
	while (*s && *s >= 9 && *s <= 32)
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			p *= -1;
	while (*s >= '0' && *s <= '9')
		r = r * 10 + (*s++ - '0');
	return (p * r);
}

#endif
