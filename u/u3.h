/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u3.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:30:24 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/09 13:49:50 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef U3_H
# define U3_H

char	*_strapnd(const char *d, const char *s);
char	*_readline_fd(const int fd);
void	_snprintf(char *b, size_t n, const char *f, ...);
void	_printffd(const int fd, const char *f, ...);

char	*_strapnd(const char *d, const char *s)
{
	char	*r;

	if (!s)
		return ((char *)d);
	if (!d)
		return (_strdup(s));
	r = _calloc(_strlen(d) + _strlen(s) + 1, sizeof(char));
	_stpcpy(_stpcpy(r, d), s);
	return (r);
}

char	*_readline_fd(const int fd)
{
	static char	buf[2];
	char		*line;
	int			len;

	_memset(buf, 0, 2);
	line = NULL;
	len = read(fd, &buf, 1);
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

void	_snprintf(char *b, size_t n, const char *f, ...)
{
	__builtin_va_list	a;
	const char			*p;
	char				*bp;
	char				*sa;

	__builtin_va_start(a, f);
	p = f;
	bp = b;
	while (*p && n--)
	{
		if (*p == '%' && *(p + 1) == 's')
		{
			sa = __builtin_va_arg(a, char *);
			bp = _stpcpy(bp, sa);
			p += 2;
		}
		else
			*bp++ = *p++;
	}
	*bp = '\0';
	__builtin_va_end(a);
}

void	_printffd(const int fd, const char *f, ...)
{
	__builtin_va_list	a;
	const char			*p;
	char				*sa;

	__builtin_va_start(a, f);
	p = f;
	while (*p)
	{
		if (*p == '%' && *(p + 1) == 's')
		{
			sa = __builtin_va_arg(a, char *);
			_putsfd(fd, sa);
			p += 2;
		}
		else
			write(fd, p++, 1);
	}
	__builtin_va_end(a);
}

#endif
