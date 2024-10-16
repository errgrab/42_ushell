/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:21:23 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/16 23:47:52 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "lib/lib.h"

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

t_sh	*g(void);

# ifdef SH

t_sh	*g(void)
{
	static t_sh	sh;

	return (&sh);
}

# endif

int		b_exit(int ac, char **av);
int		b_cd(int ac, char **av);
int		builtin(char *str, char **av, int *status);

void	_parse(char *input);

#endif
