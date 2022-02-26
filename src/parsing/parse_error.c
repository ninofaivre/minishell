/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:56:05 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/25 19:23:04 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"
#include "parsing.h"
#include <unistd.h>

static bool	parse_pipe_error(char *str)
{
	if (*str == '|')
	{
		minishell_error("parsing", NULL, VOIDPIPE);
		return (true);
	}
	while (*str)
	{
		if (*str == '|')
		{
			str++;
			str = skip_space(str);
			if (!*str || *str == '|')
			{
				minishell_error("parsing", NULL, VOIDPIPE);
				return (true);
			}
		}
		str += is_charset(*str, "><") + is_charset(str[1], "><");
		str = skip_word(str);
	}
	return (false);
}

static bool	does_redirection_content_exist(char *str, t_env *minishell_env)
{
	str = skip_space(str);
	if (!*str || is_charset(*str, "|><"))
		return (false);
	else if (*str == '$' && is_env_var_name_allowed(str[1], false))
	{
		if (str_len(get_env_var_value(minishell_env, &str[1])) == 0)
			return (false);
		else
			return (true);
	}
	else
		return (true);
}

static bool	parse_guillemet_error(char *str, t_env *minishell_env)
{
	char	quote;

	quote = '\0';
	while (*str)
	{
		quote = update_quote_status(quote, *str);
		if (is_charset(*str, "><") && quote != '\0')
		{
			str += 1 + (str[1] == *str);
			if (!does_redirection_content_exist(str, minishell_env))
			{
				if (str[-1] == '<')
					minishell_error("parsing", NULL, VOIDINPUT);
				else if (str[-1] == '>')
					minishell_error("parsing", NULL, VOIDOUTPUT);
				return (true);
			}
		}
		str++;
	}
	return (false);
}

static bool	parse_quote_error(char *str)
{
	char	quote;

	quote = update_quote_status('\0', *str);
	str++;
	while (*str)
	{
		quote = update_quote_status(quote, *str);
		str++;
	}
	if (quote == '\'')
	{
		minishell_error("parsing", NULL, UNCLOSEDSINGLEQUOTE);
		return (true);
	}
	else if (quote == '"')
	{
		minishell_error("parsing", NULL, UNCLOSEDDOUBLEQUOTE);
		return (true);
	}
	else
		return (false);
}

bool	parse_error(char *str, t_env *minishell_env)
{
	str = skip_space(str);
	if (!str || !*str)
		return (true);
	return (parse_pipe_error(str) || parse_guillemet_error(str, minishell_env)
		|| parse_quote_error(str));
}
