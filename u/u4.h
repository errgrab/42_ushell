/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u4.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 03:30:24 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/09 16:45:19 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef U4_H
# define U4_H

char	*_strapnd(const char *d, const char *s);
char	*_readline_fd(const int fd);
void	_putifd(int fd, int i);
size_t	_snprintf(char *b, size_t n, const char *f, ...);
void	_printffd(const int fd, const char *f, ...);

char	*_strapnd(const char *d, const char *s)
{
	const size_t	len = _strlen(d) + _strlen(s) + 1;
	char			*r;

	if (!s)
		return ((char *)d);
	if (!d)
		return (_strdup(s));
	r = _calloc(len, sizeof(char));
	_stpncpy(_stpncpy(r, d, len), s, len);
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

void	_putifd(int fd, int i)
{
	unsigned int	u;

	u = i;
	if (i < 0)
		u = -i;
	if (i < 0)
		write(fd, "-", 1);
	while (u >= 10)
		_putifd(fd, u / 10);
	write(fd, &"0123456789"[u % 10], 1);
}

size_t	_snprintf(char *b, size_t n, const char *f, ...)
{
	__builtin_va_list	a;
	char				*sa;
	char *const			b0 = b;
	const char			*p = f;

	__builtin_va_start(a, f);
	while (*p && n && n--)
	{
		if (*p == '%' && *(p + 1) == 's')
		{
			sa = __builtin_va_arg(a, char *);
			b = _stpncpy(b, sa, n);
			p += 2;
		}
		else
			*b++ = *p++;
	}
	*b = '\0';
	__builtin_va_end(a);
	return (b - b0);
}

void	_printffd(const int fd, const char *f, ...)
{
	__builtin_va_list	a;
	const char			*p = f;
	char				*sac;
	int					sai;

	__builtin_va_start(a, f);
	while (*p)
	{
		if (*p == '%' && *(p + 1) == 's')
		{
			sac = __builtin_va_arg(a, char *);
			_putsfd(fd, sac);
			p += 2;
		}
		else if (*p == '%' && (*(p + 1) == 'd' || *(p + 1) == 'i'))
		{
			sai = __builtin_va_arg(a, int);
			_putifd(fd, sai);
			p += 2;
		}
		else
			write(fd, p++, 1);
	}
	__builtin_va_end(a);
}

#endif
