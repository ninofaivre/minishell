/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:58:59 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/22 17:07:53 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*skip_word(char *str)
{
	t_quote	quote;

	quote = init_quote();
	str = skip_space(str);
	update_quote_status(&quote, *str);
	while (*str && (!is_charset(*str, "| ><") || quote.status == true))
	{
		str++;
		update_quote_status(&quote, *str);
	}
	str = skip_space(str);
	return (str);
}

unsigned int	word_len(char **env, char *str)
{
	t_quote			quote;
	unsigned int	len;

	quote = init_quote();
	len = 0;
	if (!str)
		return (0);
	str = skip_space(str);
	update_quote_status(&quote, *str);
	while (*str && (!is_charset(*str, "| ><") || quote.status == true))
	{
		if (!(*str == '\'' && quote.double_quote == false)
			&& !(*str == '"' && quote.single_quote == false))
		{
			if (*str == '$' && quote.single_quote == false)
				len += env_var_len(search_env_var(env, str));
			else
				len++;
		}
		str++;
		update_quote_status(&quote, *str);
	}
	return (len);
}

char	*skip_space(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (str);
}

char	*skip_var(char *str)
{
	str++;
	if (!str)
		return ((char *) NULL);
	while (*str && ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z') || (*str >= '0' && *str <= '9')))
		str++;
	return (str);
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
