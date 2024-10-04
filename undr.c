/* TODO:
 * _atoi [OK]
 * _strcmp [OK]
 * _calloc [PREV] [OK]
 * _strlen [OK]
 * _strspn [OK]
 * _strcspn [OK]
 * _strdup [OK]
 * _stpcpy (or something for concatenation) [OK]
 * _split (or some equivalent for parsing)
 * _freesplit (or some equivalent)
 * _memset (or _bzero) [OK]
 */

#ifndef _H
#define _H

typedef struct s_list	t_list;
struct s_list
{
	void	*data;
	t_list	*next;
};

#endif /* _H */

#ifdef _IMPLEMENTATION

#include <unistd.h>
#include <stdlib.h>

static t_list	**_get_CA(void)
{
	static t_list	*a;

	return (&a);
}

void	*_calloc(const size_t n, const size_t s)
{
	auto void * p = malloc(n * s);
	if (p)
	{
		auto t_list **r = _get_CA();
		auto t_list * nn = (t_list *)malloc(sizeof(t_list));
		auto size_t i = n * s;
		while (i && i--)
			((char *)p)[i] = 0;
		if (nn)
		{
			nn->data = p;
			nn->next = *r;
			*r = nn;
		}
		else
			return (free(p), NULL);
	}
	return (p);
}

void	_free(void *p)
{
	auto t_list **n = _get_CA();
	auto t_list * b = NULL;
	while (*n)
	{
		if ((*n)->data == p)
		{
			auto t_list * d = *n;
			if (b)
				b->next = (*n)->next;
			else
				*n = (*n)->next;
			free(d->data);
			free(d);
			return ;
		}
		b = *n;
		n = &(*n)->next;
	}
}

void	_clean(void)
{
	auto t_list **n = _get_CA();
	while (*n)
	{
		auto t_list * d = *n;
		*n = (*n)->next;
		free(d->data);
		free(d);
	}
}

int	_strlen(const char *s)
{
	auto int l = 0;
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

char	*_stpcpy(char *d, const char *s)
{
	while (*s)
		*d++ = *s++;
	*d = *s;
	return (d);
}

char	*_strdup(const char *s)
{
	auto char *r = _calloc(_strlen(s) + 1, sizeof(char));
	_stpcpy(r, s);
	return (r);
}

void	*_strchr(const char *s, const int c)
{
	while (*s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((void *)s);
	return (NULL);
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

void	*_memset(void *s, const int c, size_t n)
{
	while (n--)
		*((char *)s + n) = (char)c;
	return (s);
}

#endif /* _IMPLEMENTATION */
