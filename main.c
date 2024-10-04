/*
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
*/

#include <stdio.h>
#define _IMPLEMENTATION
#include "undr.c"

int main(int ac, char **av)
{
	printf(":%d:\n", ac);
	while (ac > 1)
	{
		auto char *c = _strdup(av[--ac]);
		printf("%s\n", c);
	}
	_clean();
}

/*
void ft_free(void *p)
{
	void **ptr = p;
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void err(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int is_builtin(char *str)
{
	char **builtins = (char *[]){"exit", "cd", NULL};
	int i = -1;

	while (builtins[++i])
		if (str && !ft_strcmp(builtins[i], str))
			return (1);
	return (0);
}

int ft_argc(char **argv)
{
	int i = 0;
	while (argv[i])
		i++;
	return (i);
}

int b_exit(int ac, char **av)
{
	if (ac == 1)
		return (exit(0), 1);
	else if (ac >= 2)
		return (exit(ft_atoi(av[1])), 1);
	return (1);
}

int b_cd(int ac, char **av)
{
	if (ac != 2)
		return (err("Error: cd: Invalid arguments\n"), 1);
	if (-1 == chdir(av[1]))
		return (err("Error: cd: could not change dir to "),
				err(av[1]), err("\n"), 1);
	return (1);
}

int builtin(char *str, char **av)
{
	char **builtins = (char *[]){"exit", "cd", NULL};
	int (*builtin_fn[])(int, char **) = { b_exit, b_cd, NULL};
	int i = -1;
	int ac = ft_argc(av);
	while (builtins[++i])
		if (str && !ft_strcmp(builtins[i], str))
			return (builtin_fn[i](ac, av));
	return (0);
}

char *ft_path(char *str)
{
	char **path = ft_split(getenv("PATH"), ":");
	int i = -1;
	while (path[++i])
	{
		char *res = ft_calloc(ft_strlen(path[i]) + ft_strlen(str) + 2, 1);
		if (!res)
			return (NULL);
		ft_stpcpy(ft_stpcpy(ft_stpcpy(res, path[i]), "/"), str);
		struct stat buffer = {0};
		if (stat(res, &buffer) == 0)
		{
			ft_freesplit(path);
			return (res);
		}
		ft_free(&res);
	}
	ft_freesplit(path);
	return (ft_strdup(str));
}

int exec(char **av, char **ev)
{
	if (is_builtin(av[0]))
		return (builtin(av[0], av));
	int pid = fork();
	if (-1 == pid)
		return (err("ERROR\n"), 1);
	if (!pid)
	{
		execve(ft_path(av[0]), av, ev);
		err("ERROR\n");
		exit(1);
	}
	int status;
	waitpid(pid, &status, 0);
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int main(void)
{
	char **environ;
	char *input;

	char *user = getenv("USER");
	char pwd[512] = {0};
	getcwd(pwd, 512);
	char prompt[1024] = {0};
	ft_stpcpy(ft_stpcpy(ft_stpcpy(ft_stpcpy(prompt, user), "@"), pwd), " $ ");
	input = readline(prompt);
	while (input)
	{
		add_history(input);
		char **av = ft_split(input, " \n\t");
		exec(av, envp);
		ft_freesplit(av);
		ft_free(&input);
		ft_bzero(prompt, 1024);
		getcwd(pwd, 512);
		ft_stpcpy(ft_stpcpy(ft_stpcpy(ft_stpcpy(prompt, user), "@"), pwd), " $ ");
		input = readline(prompt);
	}
	return 0;
}
*/
