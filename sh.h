/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 03:21:23 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/06 04:32:50 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

typedef struct s_shell	t_shell;
struct s_shell
{
	char	*env;
	char	*prompt;
	char	*input;
	char	*pwd;
	char	**av;
};

static t_shell	*g(void)
{
	static t_shell	shell;

	return (&shell);
}

#endif
