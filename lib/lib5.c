/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 03:25:37 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/22 19:07:38 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

t_darr	_darr_new(void);
void	_darr_put(t_darr *darr, void *ptr);
void	_darr_iter(t_darr *darr, void (*fun)(void *));
void	_darr_free(t_darr *darr);

t_darr	_darr_new(void)
{
	t_darr	res;

	res.cap = 64;
	res.len = 0;
	res.data = _calloc(res.cap, sizeof(void *));
	return (res);
}

void	_darr_put(t_darr *darr, void *ptr)
{
	size_t	ncap;
	void	**nptr;

	if (darr->len >= darr->cap)
	{
		ncap = darr->cap * 2;
		nptr = _calloc(ncap, sizeof(void *));
		_mempcpy(nptr, darr->data, darr->len * sizeof(void *));
		_free(darr->data);
		darr->data = nptr;
		darr->cap = ncap;
	}
	darr->data[darr->len] = ptr;
	darr->len++;
}

void	_darr_iter(t_darr *darr, void (*fun)(void *))
{
	size_t	len;

	if (!darr || !fun)
		return ;
	len = 0;
	while (len < darr->len)
		fun(darr->data[len++]);
}

void	_darr_free(t_darr *darr)
{
	_free(darr->data);
	darr->data = NULL;
	darr->cap = 0;
	darr->len = 0;
}
