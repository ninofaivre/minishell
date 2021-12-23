/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:01:29 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/23 16:08:03 by nfaivre          ###   ########.fr       */
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
	t_quote	quote;
	int		i;
	char	*word;

	quote = init_quote();
	i = 0;
	word = (char *)malloc(sizeof(char) * (word_len(env, str) + 1));
	if (!word)
		return ((char *) NULL);
	update_quote_status(&quote, *str);
	while (*str && (!is_charset(*str, "| ><") || quote.status == true))
	{
		if (!(*str == '\'' && !quote.double_quote)
			&& !(*str == '"' && !quote.single_quote))
		{
			if (*str == '$' && quote.single_quote == false && is_alnum(*(str + 1)) == true)
			{
				i += add_env_var_to_word(word, search_env_var(env, str));
				str = skip_var(str);
			}
			else
				word[i++] = *str++;
		}
		else
			str++;
		update_quote_status(&quote, *str);
	}
	word[i] = '\0';
	return (word);
}

char	**get_output_input(char **env, char *input, char guillemet)
{
	char	**word;

	word = (char **) NULL;
	while (*input && *input != '|')
	{
		input = skip_space(input);
		if (*input == guillemet)
		{
			input += 1 + (*(input + 1) == guillemet);
			word = add_str_to_str_tab(word, get_one_word(env, input));
			input = skip_word(input);
		}
		else
		{
			if (is_charset(*input, "><"))
				input += 1 + (is_charset(*(input + 1), "><"));
			input = skip_word(input);
		}
	}
	return (word);
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
			input += 1 + is_charset(*(input + 1), "><");
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
