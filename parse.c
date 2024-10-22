/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarvalh <ecarvalh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:15:15 by ecarvalh          #+#    #+#             */
/*   Updated: 2024/10/22 20:25:23 by ecarvalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "lib/lib.h"

void	_parse(char *input);

static size_t	toklen(char *input)
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
			len += _strcspn(&input[len + 1], quote) + 1;
			len += input[len] == quote[0];
		}
		else
			len += _strcspn(&input[len], " <|>'\"\n\t");
	}
	if (!len)
		len = _strspn(input, "<|>");
	return (len);
}

static char	*handle_var(char **input, char *res)
{
	char	*env;
	char	*str;
	size_t	len;

	(*input)++;
	len = _strcspn(*input, " $<|>'\"\n\t");
	env = _strndup(*input, len);
	str = getenv(env);
	if (str)
		res = _strjoin(res, str);
	*input += len;
	_free(env);
	return (res);
}

static char	*handle_else(char **input, char *res, char quote)
{
	char	*str;
	size_t	len;

	len = _strcspn(*input, "$'\"");
	len += quote == '\'' && **input == '$';
	str = _strndup(*input, len);
	res = _strjoin(res, str);
	_free(str);
	*input += len;
	return (res);
}

static char	*expand(char *input)
{
	char		*res;
	char		quote;

	res = _strdup("");
	if (!res)
		return (NULL);
	quote = 0;
	while (*input)
	{
		if (*input == '"' || *input == '\'')
		{
			if (quote == *input)
				quote = 0;
			else if (!quote)
				quote = *input;
			input++;
		}
		if (*input == '$' && quote != '\'')
			res = handle_var(&input, res);
		else
			res = handle_else(&input, res, quote);
	}
	return (res);
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
		_darr_put(&res, expand(_strndup(input, len)));
		input += len;
	}
	_darr_put(&res, NULL);
	g()->parsed = res;
}
