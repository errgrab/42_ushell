/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:33:22 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/16 23:44:24 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lib/lib.h"

int		b_exit(int ac, char **av);
int		b_cd(int ac, char **av);
int		builtin(char *str, char **av, int *status);
void	_parse(char *input);

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
	char	*dir;

	if (ac > 2)
		return (_printffd(2, "Error: cd: Invalid arguments\n"), 1);
	else if (ac == 1)
		dir = getenv("HOME");
	else
		dir = av[1];
	if (-1 == chdir(dir))
		return (_printffd(2, "Error: cd: %s: No such directory\n", av[1]), 1);
	return (1);
}

int	builtin(char *str, char **av, int *status)
{
	char	**builtins;
	int		(**builtin_fn)(int, char **);
	int		i;
	int		ac;

	builtins = (char *[]){"exit", "cd", NULL};
	builtin_fn = (int (*[])(int ac, char **av)){b_exit, b_cd, NULL};
	i = -1;
	ac = 0;
	while (av[ac])
		ac++;
	while (builtins[++i])
		if (str && !_strcmp(builtins[i], str))
			return (*status = builtin_fn[i](ac, av), 1);
	return (0);
}

size_t	toklen(char *input)
{
	size_t	len;
	char	*quote;

	len = 0;
	while (input[len] && (_strchr("'\"", input[len])
			|| _strcspn(&input[len], " <|>'\"\n\t")))
	{
		if (_strchr("'\"", input[len]))
		{
			quote = (char []){input[len], 0};
			len += _strcspn(&input[len] + 1, quote) + 1;
			len += input[len] == quote[0];
		}
		else
			len += _strcspn(&input[len], " <|>'\"\n\t");
	}
	if (!len)
		len = _strspn(input, "<|>");
	return (len);
}

void	_parse(char *input)
{
	t_darr	res;
	size_t	len;

	res = _darr_new();
	while (*input)
	{
		len = 0;
		input += _strspn(input, " \n\t");
		len = toklen(input);
		_darr_put(&res, _strndup(input, len));
		input += len;
	}
	_darr_put(&res, NULL);
	g()->parsed = res;
}
