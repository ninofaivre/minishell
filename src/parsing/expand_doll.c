/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_doll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:19:43 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/05 01:17:58 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static int	var_name_size(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (is_env_var_name_allowed(str[len], false) && str[len])
		len++;
	return (len);
}

static int	expanded_size(char *str, int status, t_env *minishell_env)
{
	int		len;
	char	quote;

	len = 0;
	quote = update_quote_status('\0', *str);
	while (*str)
	{
		if (*str == '$' && is_env_var_name_allowed(str[1], true)
			&& quote != '\'')
		{
			len += str_len(get_env_var_value(minishell_env, &str[1]));
			str += var_name_size(&str[1]);
		}
		else if (*str == '$' && str[1] == '?' && quote != '\'')
		{
			len += int_len(status);
			str++;
		}
		else
			len++;
		str++;
		quote = update_quote_status(quote, *str);
	}
	return (len + 1);
}

static int	cpy_status(char *expanded_str, int status)
{
	char	*str_status;

	str_status = itoa(status);
	if (!str_status)
		return (true);
	str_ncpy(expanded_str, str_status, str_len(str_status));
	free(str_status);
	return (false);
}

static bool	put_str_expanded(char *expanded_str, char *str,
int status, t_env *minishell_env)
{
	char	quote;

	quote = update_quote_status('\0', *str);
	while (*str)
	{
		if (*str == '$' && is_env_var_name_allowed(str[1], true)
			&& quote != '\'')
		{
			str_ncpy(expanded_str, get_env_var_value(minishell_env, \
			&str[1]), str_len(get_env_var_value(minishell_env, &str[1])));
			expanded_str += str_len(get_env_var_value(minishell_env, &str[1]));
			str += var_name_size(&str[1]);
		}
		else if (*str == '$' && str[1] == '?' && quote != '\'' && *str++)
		{
			if (cpy_status(expanded_str, status))
				return (true);
			expanded_str += int_len(status);
		}
		else
			*expanded_str++ = *str;
		quote = update_quote_status(quote, str++[1]);
	}
	*expanded_str = '\0';
	return (false);
}

char	*expand_doll(char *str, int status, t_env *minishell_env)
{
	char	*expanded_str;

	expanded_str = malloc(expanded_size(str, status, minishell_env));
	if (!expanded_str)
		return (NULL);
	else if (put_str_expanded(expanded_str, str, status, minishell_env))
	{
		free(expanded_str);
		return (NULL);
	}
	else
		return (expanded_str);
}
