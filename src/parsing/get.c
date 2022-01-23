/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:01:29 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/23 18:29:01 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

int	cpy_status(char *word, int status)
{
	int		i;
	char	*str_status;

	i = 0;
	str_status = itoa(status);
	while (str_status[i])
		*word++ = str_status[i++];
	free(str_status);
	return (int_len(status));
}

static void	cpy_word(t_var *var, char *word, char *str, char quote)
{
	int		i;

	i = 0;
	while (*str && (!is_charset(*str, "| ><") || quote != '\0'))
	{
		if (!(is_charset(*str, "'\"") && (quote == '\0' || quote == *str)))
		{
			if (*str == '$' && quote != '\'' && is_alnum(str[1]))
			{
				i += add_env_var_to_word(&word[i], search_env_var(*(var->env), str));
				str = skip_var(str);
			}
			else if (*str == '$' && quote != '\'' && str[1] == '?')
			{
				i += cpy_status(&word[i], var->status);
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

t_redirection	*get_redirection(t_var *var, char *input, char guillemet)
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
			redirection[i++].content = get_one_word(var, input);
			input = skip_word(input);
		}
		else
		{
			if (is_charset(*input, "><"))
				input += 1 + (is_charset(input[1], "><"));
			input = skip_word(input);
		}
	}
	redirection[i].content = (char *) NULL;
	return (redirection);
}

char	**get_argv(t_var *var, char *input)
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
			argv = add_str_to_str_tab(argv, get_one_word(var, input));
			input = skip_word(input);
		}
	}
	return (argv);
}
