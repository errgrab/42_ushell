/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e.h                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:33:22 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/04 15:35:58 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef E_H
# define E_H

int	b_exit(int ac, char **av);
int	b_cd(int ac, char **av);
int	builtin(char *str, char **av, int *status);

int	b_exit(int ac, char **av)
{
	if (ac == 1)
		return (exit(0), 1);
	else if (ac >= 2)
		return (exit(_atoi(av[1])), 1);
	return (1);
}

int	b_cd(int ac, char **av)
{
	if (ac != 2)
		return (_err("Error: cd: Invalid arguments\n"), 1);
	if (-1 == chdir(av[1]))
		return (_err("Error: cd: could not change dir to "),
			_err(av[1]), _err("\n"), 1);
	return (1);
}

int	builtin(char *str, char **av, int *status)
{
	auto char **builtins = (char *[]){"exit", "cd", NULL};
	auto int (*builtin_fn[])(int, char **) = {b_exit, b_cd, NULL};
	auto int i = -1;
	auto int ac = 0;
	while (av[ac])
		ac++;
	while (builtins[++i])
		if (str && !_strcmp(builtins[i], str))
			return (*status = builtin_fn[i](ac, av), 1);
	return (0);
}

#endif
