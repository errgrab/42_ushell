/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ualloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 01:25:21 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/09 14:02:46 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UALLOC_H
# define UALLOC_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_u_l	t_u_l;
struct s_u_l
{
	void	*data;
	t_u_l	*next;
};

void	*_calloc(const size_t n, const size_t s);
void	_free(void *p);
void	_clean(void);

static t_u_l	**_get_ca(void)
{
	static t_u_l	*ca = NULL;

	return (&ca);
}

void	*_calloc(const size_t n, const size_t s)
{
	size_t	len;
	void	*res;
	t_u_l	*lnew;
	t_u_l	**root;

	len = n * s;
	res = malloc(len);
	if (!res)
		return (NULL);
	lnew = (t_u_l *)malloc(sizeof(t_u_l));
	if (!lnew)
		return (free(res), NULL);
	while (len && len--)
		((char *)res)[len] = 0;
	root = _get_ca();
	lnew->data = res;
	lnew->next = *root;
	*root = lnew;
	return (res);
}

void	_free(void *p)
{
	t_u_l	**node;
	t_u_l	*prev;
	t_u_l	*del;

	node = _get_ca();
	prev = NULL;
	while (*node)
	{
		if ((*node)->data == p)
		{
			del = *node;
			if (prev)
				prev->next = (*node)->next;
			else
				*node = (*node)->next;
			free(del->data);
			free(del);
			return ;
		}
		prev = *node;
		node = &(*node)->next;
	}
}

void	_clean(void)
{
	t_u_l	**node;
	t_u_l	*del;

	node = _get_ca();
	while (*node)
	{
		del = *node;
		*node = (*node)->next;
		free(del->data);
		free(del);
	}
}

#endif
