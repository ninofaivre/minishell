/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:01:29 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/21 14:42:21 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static void	cpy_word(t_var *var, char *word, char *str, char quote)
{
	while (*str && (!is_charset(*str, "| ><") || quote != '\0'))
	{
		if (!(is_charset(*str, "'\"") && (quote == '\0' || quote == *str)))
		{
			if (*str == '$' && quote != '\'' && is_env_var_name_allowed(str[1]))
			{
				word += add_str_word(word, \
				get_env_var_value(var->minishell_env, &str[1]));
				str = skip_var(str);
			}
			else if (*str == '$' && quote != '\'' && str[1] == '?')
			{
				word += add_int_word(word, var->status);
				str += 2;
			}
			else
				*word++ = *str++;
		}
		else
			str++;
		quote = update_quote_status(quote, *str);
	}
	*word = '\0';
}

static char	*get_one_word(t_var *var, char *str)
{
	char	quote;
	char	*word;

	quote = update_quote_status('\0', *str);
	word = malloc(sizeof(char) * (word_len(var, str) + 1));
	if (!word)
		return (NULL);
	cpy_word(var, word, str, quote);
	return (word);
}

t_redirection	*get_redirection(t_var *var, char *input)
{
	int				i;
	t_redirection	*redirection;

	i = 0;
	redirection = malloc(sizeof(t_redirection)
			* (count_redirection(input) + 1));
	if (!redirection)
		return (NULL);
	while (*input && *input != '|')
	{
		input = skip_space(input);
		if (is_charset(*input, "><"))
		{
			redirection[i].is_double = is_charset(input[1], "><");
			redirection[i].guillemet = *input;
			input = skip_space(&input[1 + (is_charset(input[1], "><"))]);
			redirection[i++].content = get_one_word(var, input);
			if (!redirection[i - 1].content)
				return (free_redirection(redirection));
		}
		input = skip_word(input);
	}
	redirection[i].content = NULL;
	return (redirection);
}

static bool	null_word(t_var *var, char *input)
{
	bool	is_there_doll;
	bool	is_there_quote;

	if (!input || word_len(var, input))
		return (false);
	is_there_doll = false;
	is_there_quote = false;
	while (*input && !is_charset(*input, "| ><"))
	{
		if (*input == '$')
			is_there_doll = true;
		else if (*input == '"')
			is_there_quote = true;
		input++;
	}
	if (is_there_doll == true && is_there_quote == false)
		return (true);
	else
		return (false);
}

char	**get_argv(t_var *var, char *input)
{
	char	**argv;

	argv = malloc(sizeof(char *) * 1);
	if (!argv)
		return (NULL);
	argv[0] = NULL;
	while (*input && *input != '|')
	{
		input = skip_space(input);
		if (is_charset(*input, "><"))
			input = skip_word(&input[1 + is_charset(input[1], "><")]);
		else
		{
			if (!null_word(var, input))
			{
				argv = add_str_to_str_tab(argv, get_one_word(var, input));
				if (!argv)
					return (NULL);
			}
			input = skip_word(input);
		}
	}
	return (argv);
}
