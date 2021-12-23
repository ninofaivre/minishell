/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:58:59 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/23 16:16:02 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	is_alnum(char c)
{
	if (!c)
		return (false);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return (true);
	else
		return (false);
}

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
		if (!(*str == '\'' && quote.double_q == false)
			&& !(*str == '"' && quote.single_q == false))
		{
			if (*str == '$' && quote.single_q == false && is_alnum(*(str + 1)) == true)
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
	while (*str && is_alnum(*str) == true)
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