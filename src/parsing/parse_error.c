/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 18:56:05 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/15 20:34:09 by nfaivre          ###   ########.fr       */
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

static bool	parse_guillemet_error(t_var *var, char *str)
{
	while (*str)
	{
		str += (*str == '|');
		if (is_charset(*str, "><"))
		{
			str += 1 + (str[1] == *str);
			if (!word_len(var, str) && str[-1] == '<')
			{
				minishell_error("parsing", NULL, VOIDINPUT);
				return (true);
			}
			else if (!word_len(var, str) && str[-1] == '>')
			{
				minishell_error("parsing", NULL, VOIDOUTPUT);
				return (true);
			}
		}
		str = skip_word(str);
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

bool	parse_error(t_var *var, char *str)
{
	str = skip_space(str);
	if (!str || !*str)
		return (true);
	if (parse_pipe_error(str))
		return (true);
	if (parse_guillemet_error(var, str))
		return (true);
	if (parse_quote_error(str))
		return (true);
	return (false);
}
