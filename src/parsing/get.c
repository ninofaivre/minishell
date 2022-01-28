/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:01:29 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/28 16:32:24 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static void	cpy_word(t_var *var, char *word, char *str, char quote)
{
	int		i;

	i = 0;
	while (*str && (!is_charset(*str, "| ><") || quote != '\0'))
	{
		if (!(is_charset(*str, "'\"") && (quote == '\0' || quote == *str)))
		{
			if (*str == '$' && quote != '\'' && is_env_var_name_allowed(str[1]))
			{
				i += add_str_word(&word[i], env_var_value(*(var->env), str));
				str = skip_var(str);
			}
			else if (*str == '$' && quote != '\'' && str[1] == '?')
			{
				i += add_int_word(&word[i], var->status);
				str += 2;
			}
			else
				word[i++] = *str++;
		}
		else
			str++;
		quote = update_quote_status(quote, *str);
	}
	word[i] = '\0';
}

static char	*get_one_word(t_var *var, char *str)
{
	char	quote;
	char	*word;

	quote = update_quote_status('\0', *str);
	word = (char *)malloc(sizeof(char) * (word_len(var, str) + 1));
	if (!word)
		return ((char *) NULL);
	cpy_word(var, word, str, quote);
	return (word);
}

t_redirection	*get_redirection(t_var *var, char *input)
{
	int				i;
	t_redirection	*redirection;

	i = 0;
	redirection = (t_redirection *)malloc(sizeof(t_redirection)
			* (count_redirection(input) + 1));
	if (!redirection)
		return ((t_redirection *) NULL);
	while (*input && *input != '|')
	{
		input = skip_space(input);
		if (is_charset(*input, "><"))
		{
			if (is_charset(input[1], "><"))
				redirection[i].is_double = true;
			redirection[i].guillemet = *input;
			input += 1 + (is_charset(input[1], "><"));
			input = skip_space(input);
			redirection[i++].content = get_one_word(var, input);
			if (!redirection[i - 1].content)
				return (free_redirection(redirection));
		}
		input = skip_word(input);
	}
	redirection[i].content = (char *) NULL;
	return (redirection);
}

char	**get_argv(t_var *var, char *input)
{
	char	**argv;

	argv = (char **)malloc(sizeof(char *) * 1);
	if (!argv)
		return ((char **) NULL);
	argv[0] = (char *) NULL;
	while (*input && *input != '|')
	{
		input = skip_space(input);
		if (is_charset(*input, "><"))
		{
			input += 1 + is_charset(input[1], "><");
			input = skip_word(input);
		}
		else
		{
			argv = add_str_to_str_tab(argv, get_one_word(var, input));
			if (!argv)
				return ((char **) NULL);
			input = skip_word(input);
		}
	}
	return (argv);
}
