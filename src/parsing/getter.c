/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:01:29 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/30 15:46:09 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

static int	add_env_var_to_word(char *word, char *env_var)
{
	unsigned int	env_var_len;

	env_var_len = str_len(env_var);
	while (env_var && *env_var)
		*word++ = *env_var++;
	return (env_var_len);
}

static char	*get_one_word(char **env, char *str)
{
	char	quote;
	int		i;
	char	*word;

	quote = update_quote_status('\0', *str);
	i = 0;
	word = (char *)malloc(sizeof(char) * (word_len(env, str) + 1));
	if (!word)
		return ((char *) NULL);
	while (*str && (!is_charset(*str, "| ><") || quote != '\0'))
	{
		if (!(is_charset(*str, "'\"") && (quote == '\0' || quote == *str)))
		{
			if (*str == '$' && quote != '\'' && is_alnum(str[1]))
			{
				i += add_env_var_to_word(word, search_env_var(env, str));
				str = skip_var(str);
			}
			else
				word[i++] = *str++;
		}
		else
			str++;
		quote = update_quote_status(quote, *str);
	}
	word[i] = '\0';
	return (word);
}

char	*get_next_pipe(char *str)
{
	if (!str || !*str)
		return ((char *) NULL);
	while (*str && *str != '|')
	{
		str = skip_word(str);
		if (is_charset(*str, "><"))
			str++;
	}
	if (*str == '|')
		str++;
	return (str);
}

int	count_redirection(char *str, char guillemet)
{
	int	n_redirection;

	n_redirection = 0;
	while (*str && *str != '|')
	{
		if (is_charset(*str, "><"))
		{
			n_redirection += (*str == guillemet) + (str[1] == guillemet);
			str += (is_charset(*str, "><")) + (is_charset(str[1], "><"));
		}
		str = skip_word(str);
	}
	return (n_redirection);
}

t_redirection	*get_redirection(char **env, char *input, char guillemet)
{
	int				i;
	t_redirection	*redirection;

	i = 0;
	redirection = (t_redirection *)malloc(sizeof(t_redirection)
			* (count_redirection(input, guillemet) + 1));
	while (*input && *input != '|')
	{
		input = skip_space(input);
		if (*input == guillemet)
		{
			if (input[1] == guillemet)
				redirection[i].is_double = true;
			input += 1 + (input[1] == guillemet);
			input = skip_space(input);
			redirection[i++].content = get_one_word(env, input);
			input = skip_word(input);
		}
		else
		{
			if (is_charset(*input, "><"))
				input += 1 + (is_charset(input[1], "><"));
			input = skip_word(input);
		}
		redirection[i].content = (char *) NULL;
	}
	return (redirection);
}

char	**get_argv(char **env, char *input)
{
	char	**argv;

	argv = (char **) NULL;
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
			argv = add_str_to_str_tab(argv, get_one_word(env, input));
			input = skip_word(input);
		}
	}
	return (argv);
}
