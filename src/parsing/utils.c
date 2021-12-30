/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:58:59 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/30 16:16:42 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	is_alnum(char c)
{
	if (!c)
		return (false);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (true);
	else
		return (false);
}

unsigned int	word_len(char **env, char *str)
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
			if (*str == '$' && quote != '\'' && is_alnum(*(str + 1)))
			{
				len += str_len(search_env_var(env, str));
				str = skip_var(str);
			}
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

bool	is_charset(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (true);
		charset++;
	}
	return (false);
}

unsigned int	str_len(char *str)
{
	unsigned int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}
