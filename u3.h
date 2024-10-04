/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u3.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:30:24 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/04 03:39:56 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef U3_H
# define U3_H

char	*_strapnd(const char *d, const char *s);
char	*_readline_fd(const int fd);

char	*_strapnd(const char *d, const char *s)
{
	if (!s)
		return (d);
	if (!d)
		return (_strdup(s));
	auto char *r = _calloc(_strlen(d) + _strlen(s) + 1, sizeof(char));
	_stpcpy(_stpcpy(r, d), s);
	return (r);
}

char	*_readline_fd(const int fd)
{
	auto char buf[2] = {0};
	auto char *line = NULL;
	auto int len = read(fd, &buf, 1);
	while (len > 0)
	{
		buf[len] = 0;
		line = _strapnd(line, buf);
		if (*buf == '\n')
			break ;
		len = read(fd, &buf, 1);
	}
	if (len < 0)
		return (_free(line), NULL);
	return (line);
}

#endif
