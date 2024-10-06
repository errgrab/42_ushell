/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ualloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 01:25:21 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/06 02:52:49 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UALLOC_H
# define UALLOC_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_u_l	t_u_l;
struct s_u_l
{
	void	*d;
	t_u_l	*n;
};

void	*_calloc(const size_t n, const size_t s);
void	_free(void *p);
void	_clean(void);

static t_u_l	**_get_ca(void)
{
	static t_u_l	*a = NULL;

	return (&a);
}

void	*_calloc(const size_t n, const size_t s)
{
	void	*p;
	t_u_l	**r;
	t_u_l	*nn;
	size_t	i;

	p = malloc(n * s);
	if (!p)
		return (NULL);
	nn = (t_u_l *)malloc(sizeof(t_u_l));
	if (!nn)
		return (free(p), NULL);
	i = n * s;
	while (i && i--)
		((char *)p)[i] = 0;
	r = _get_ca();
	nn->d = p;
	nn->n = *r;
	*r = nn;
	return (p);
}

void	_free(void *p)
{
	t_u_l	**n;
	t_u_l	*b;
	t_u_l	*d;

	n = _get_ca();
	b = NULL;
	while (*n)
	{
		if ((*n)->d == p)
		{
			d = *n;
			if (b)
				b->n = (*n)->n;
			else
				*n = (*n)->n;
			free(d->d);
			free(d);
			return ;
		}
		b = *n;
		n = &(*n)->n;
	}
}

void	_clean(void)
{
	t_u_l	**n;
	t_u_l	*d;

	n = _get_ca();
	while (*n)
	{
		d = *n;
		*n = (*n)->n;
		free(d->d);
		free(d);
	}
}

#endif
