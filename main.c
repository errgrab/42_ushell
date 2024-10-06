/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 15:27:06 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/06 02:20:54 by ecarvalh         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	auto char *user = getenv("USER");
	auto char pwd[512] = {0};
	auto char prompt[1024] = {0};
	_memset(prompt, 0, 1024);
	getcwd(pwd, 512);
	_sprintf(prompt, "[%s@%s] $ ", user, pwd);
	auto char *input = readline(prompt);
	while (input)
	{
		add_history(input);
		auto char **av = _split(input, " \n\t");
		exec(av, envp);
		_splitfree(av);
		_free(input);
		_memset(prompt, 0, 1024);
		getcwd(pwd, 512);
		_sprintf(prompt, "[%s@%s] $ ", user, pwd);
		input = readline(prompt);
	}
	rl_clear_history();
	_clean();
	return (0);
}
