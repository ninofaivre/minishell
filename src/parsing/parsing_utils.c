/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:58:59 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/25 19:36:41 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

unsigned int	word_len(char *str)
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
			len++;
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
