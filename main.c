/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:27:06 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/15 10:32:08 by ecarvalh         ###   ########.fr       */
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
#define U_IMPL
#include "u/u.h"
#include "sh.h"
#define E_IMPL
#include "e.h"

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
	getcwd(sh->pwd, 32);
	if (!_strcmp(sh->pwd, getenv("HOME")))
		_strlcpy(sh->pwd, "~", 32);
	_snprintf(sh->prompt, 64, "[%s] %s $ ", user, sh->pwd);
}

int	init_shell(void)
{
	t_sh	*sh;

	sh = g();
	sh->prompt = _calloc(64, sizeof(char));
	sh->pwd = _calloc(32, sizeof(char));
	if (!sh->prompt || !sh->pwd)
		return (_putsfd(2, "Error: Not possible to initialize shell\n"), 1);
	update_prompt();
	sh->input = readline(sh->prompt);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_sh	*sh;

	(void)envp;
	sh = g();
	sh->ac = ac;
	sh->av = &av[1];
	if (init_shell())
		return (1);
	while (sh->input)
	{
		add_history(sh->input);
		_parse(sh->input);
		av = (char **)sh->parsed.data;
		if (av[0])
			exec(av, envp);
		_darr_free(&sh->parsed);
		_free(sh->input);
		update_prompt();
		sh->input = readline(sh->prompt);
	}
	rl_clear_history();
	_clean();
	return (0);
}
