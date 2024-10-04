/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u3.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:30:24 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/04 15:12:25 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef U3_H
# define U3_H

char	*_strapnd(const char *d, const char *s);
char	*_readline_fd(const int fd);
void	_sprintf(char *b, const char *f, ...);

char	*_strapnd(const char *d, const char *s)
{
	if (!s)
		return ((char *)d);
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

void	_sprintf(char *b, const char *f, ...)
{
	__builtin_va_list a;
	__builtin_va_start(a, f);
	auto const char *p = f;
	auto char *bp = b;
	while (*p)
	{
		if (*p == '%' && *(p + 1) == 's')
		{
			auto char *sa = __builtin_va_arg(a, char *);
			bp = _stpcpy(bp, sa);
			p += 2;
		}
		else
			*bp++ = *p++;
	}
	*bp = 0;
	__builtin_va_end(a);
}

#endif
