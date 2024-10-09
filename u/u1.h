/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u1.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 01:45:16 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/09 16:39:50 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef U1_H
# define U1_H

char	*_strdup(const char *s);
char	*_strndup(const char *s, const size_t n);
int		_strspn(const char *s, const char *a);
int		_strcspn(const char *s, const char *r);
int		_atoi(const char *s);

char	*_strdup(const char *s)
{
	const size_t	len = _strlen(s) + 1;
	char *const		r = _calloc(len, sizeof(char));

	_stpncpy(r, s, len);
	return (r);
}

char	*_strndup(const char *s, const size_t n)
{
	size_t	l;
	char	*r;

	l = _strlen(s);
	if (n < l)
		l = n;
	r = _calloc(l + 1, sizeof(char));
	if (!r)
		return (NULL);
	r[l] = 0;
	while (l--)
		r[l] = s[l];
	return (r);
}

int	_strspn(const char *s, const char *a)
{
	int	l;

	l = 0;
	while (s[l] && _strchr(a, s[l]))
		l++;
	return (l);
}

int	_strcspn(const char *s, const char *r)
{
	int	l;

	l = 0;
	while (s[l] && !_strchr(r, s[l]))
		l++;
	return (l);
}

int	_atoi(const char *s)
{
	int	r;
	int	p;

	r = 0;
	p = 1;
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
