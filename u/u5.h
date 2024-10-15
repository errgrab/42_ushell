/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u5.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 03:25:37 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/15 14:18:23 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef U5_H
# define U5_H

typedef struct s_darr	t_darr;
struct s_darr
{
	size_t	cap;
	size_t	len;
	void	**data;
};

t_darr	_darr_new(void);
void	_darr_put(t_darr *darr, void *ptr);
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

void	_darr_free(t_darr *darr)
{
	_free(darr->data);
	darr->data = NULL;
	darr->cap = 0;
	darr->len = 0;
}

#endif // U5_H
