/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:27:06 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/09 13:48:03 by ecarvalh         ###   ########.fr       */
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
	int			len;

	path = _split(getenv("PATH"), ":");
	i = -1;
	while (path[++i])
	{
		len = _strlen(path[i]) + _strlen(str) + 2;
		res = _calloc(len, 1);
		if (!res)
			return (NULL);
		_snprintf(res, len, "%s/%s", path[i], str);
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
	int		status;
	int		pid;

	if (builtin(av[0], av, &status))
		return (status);
	pid = fork();
	if (-1 == pid)
		return (_printffd(2, "Error: Could not start process"), 1);
	if (!pid)
	{
		execve(ft_path(av[0]), av, ev);
		_printffd(2, "Error: %s: Command not found\n", av[0]);
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
	if (!_strcmp(sh->pwd, getenv("HOME")))
		sh->pwd = "~";
	_snprintf(sh->prompt, 64, "[%s] %s $ ", user, sh->pwd);
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
