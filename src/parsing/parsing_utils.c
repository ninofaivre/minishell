/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:58:59 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/21 16:00:35 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static char	*env_var_len(t_var *var, char *str, unsigned int *len)
{
	if (is_env_var_name_allowed(str[1]))
	{
		*len += str_len(get_env_var_value(var->minishell_env, &str[1]));
		str = skip_var(str);
	}
	else if (str[1] == '?')
	{
		*len += int_len(var->status);
		str += 2;
	}
	else
	{
		*len += 1;
		str++;
	}
	return (str);
}

unsigned int	word_len(t_var *var, char *str)
{
	char			quote;
	unsigned int	len;

	len = 0;
	if (!str)
		return (0);
	str = skip_space(str);
	quote = update_quote_status('\0', *str);
	while (*str && (!is_charset(*str, "| ><") || quote != '\0'))
	{
		if (!(*str == '\'' && quote != '"') && !(*str == '"' && quote != '\''))
		{
			if (*str == '$' && quote != '\'')
				str = env_var_len(var, str, &len);
			else
			{
				len++;
				str++;
			}
		}
		else
			str++;
		quote = update_quote_status(quote, *str);
	}
	return (len);
}

char	update_quote_status(char quote, char c)
{
	if (quote == '\0' && is_charset(c, "'\""))
		return (c);
	else if (quote != '\0' && quote == c)
		return ('\0');
	else
		return (quote);
}
