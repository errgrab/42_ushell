/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u2.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 02:07:57 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/09 13:43:17 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef U2_H
# define U2_H

# include "u.h"

int		_wc(const char *s, const char *d);
char	**_split(const char *s, const char *d);
void	_splitfree(char **s);
void	_putsfd(const int fd, const char *s);
void	_putsnfd(const int fd, const char *s, size_t n);

int	_wc(const char *s, const char *d)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (s[i])
	{
		i += _strspn(&s[i], d);
		if (s[i])
		{
			i += _strcspn(&s[i], d);
			c++;
		}
	}
	return (c);
}

char	**_split(const char *s, const char *d)
{
	const char	*t;
	char		**r;
	int			i;

	r = (char **)_calloc(_wc(s, d) + 1, sizeof(char *));
	if (!r)
		return (NULL);
	t = NULL;
	t = s + _strspn(s, d);
	s = t + _strcspn(t, d);
	i = -1;
	while (*t)
	{
		r[++i] = _strndup(t, s - t);
		if (!r[i])
			return (_splitfree(r), NULL);
		t = s + _strspn(s, d);
		s = t + _strcspn(t, d);
	}
	r[++i] = NULL;
	return (r);
}

void	_splitfree(char **s)
{
	int	i;

	i = -1;
	while (s[++i])
		_free(s[i]);
	_free(s);
}

void	_putsfd(const int fd, const char *s)
{
	while (*s)
		write(fd, s++, 1);
}

void	_putsnfd(const int fd, const char *s, size_t n)
{
	while (*s && n--)
		write(fd, s++, 1);
}

#endif
