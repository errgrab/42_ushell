/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:27:06 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/07 14:38:53 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "u/u.h"
#include "e.h"
#include "sh.h"

char	*ft_path(char *str)
{
	struct stat	b;
	char		**path;
	int			i;
	char		*res;

	path = _split(getenv("PATH"), ":");
	i = -1;
	while (path[++i])
	{
		res = _calloc(_strlen(path[i]) + _strlen(str) + 2, 1);
		if (!res)
			return (NULL);
		_sprintf(res, "%s/%s", path[i], str);
		if (stat(res, &b) == 0)
		{
			_splitfree(path);
			return (res);
		}
		_free(res);
	}
	_splitfree(path);
	return (_strdup(str));
}

int	exec(char **av, char **ev)
{
	int	status;
	int	pid;

	if (builtin(av[0], av, &status))
		return (status);
	pid = fork();
	if (-1 == pid)
		return (_err("ERROR\n"), 1);
	if (!pid)
	{
		execve(ft_path(av[0]), av, ev);
		_err("ERROR\n");
		exit(1);
	}
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

void	update_prompt(void)
{
	const char	*user = getenv("USER");
	t_sh		*sh;

	sh = g();
	sh->pwd = _calloc(32, sizeof(char));
	getcwd(sh->pwd, 32);
	_sprintf(sh->prompt, "[%s] %s $ ", user, sh->pwd);
}

void	init_shell(void)
{
	t_sh	*sh;

	sh = g();
	sh->prompt = _calloc(64, sizeof(char));
	update_prompt();
	sh->input = readline(sh->prompt);
}

int	main(int ac, char **av, char **envp)
{
	t_sh	*sh;

	sh = g();
	if (ac > 0)
		sh->av = &av[1];
	init_shell();
	while (sh->input)
	{
		add_history(sh->input);
		av = _split(sh->input, " \n\t");
		exec(av, envp);
		_splitfree(av);
		_free(sh->input);
		update_prompt();
		sh->input = readline(sh->prompt);
	}
	rl_clear_history();
	_clean();
	return (0);
}
