/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:21:23 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/06 04:35:51 by ecarvalh         ###   ########.fr       */
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
	char	**av;
};

static t_sh	*g(void)
{
	static t_sh	sh;

	return (&sh);
}

#endif
