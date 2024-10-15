/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:21:23 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/15 14:18:32 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

typedef struct s_sh	t_sh;
struct s_sh
{
	char	*env;
	char	*prompt;
	char	*input;
	char	*pwd;
	int		ac;
	char	**av;
	t_darr	parsed;
};

static t_sh	*g(void)
{
	static t_sh	sh;

	return (&sh);
}

#endif
