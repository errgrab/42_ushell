/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:27:06 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/06 04:31:50 by ecarvalh         ###   ########.fr       */
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

	auto char **path = _split(getenv("PATH"), ":");
	auto int i = -1;
	while (path[++i])
	{
		auto char *res = _calloc(_strlen(path[i]) + _strlen(str) + 2, 1);
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
	auto int status;
	if (builtin(av[0], av, &status))
		return (status);
	auto int pid = fork();
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

	g()->pwd = _calloc(32, sizeof(char));
	getcwd(g()->pwd, 32);
	_sprintf(g()->prompt, "[%s] %s $ ", user, g()->pwd);
}

void	init_shell(void)
{
	t_shell	*sh;

	sh = g();
	sh->prompt = _calloc(64, sizeof(char));
	update_prompt();
	sh->input = readline(sh->prompt);
}

int	main(int ac, char **av, char **envp)
{
	if (ac > 0)
		g()->av = &av[1];
	init_shell();
	g()->input = readline(g()->prompt);
	while (g()->input)
	{
		add_history(g()->input);
		av = _split(g()->input, " \n\t");
		exec(av, envp);
		_splitfree(av);
		_free(g()->input);
		update_prompt();
		g()->input = readline(g()->prompt);
	}
	rl_clear_history();
	_clean();
	return (0);
}
