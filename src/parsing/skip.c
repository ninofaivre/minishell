/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 16:16:10 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/25 19:36:34 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <unistd.h>

char	*skip_space(char *str)
{
	if (!str)
		return (NULL);
	while (*str && *str == ' ')
		str++;
	return (str);
}

char	*skip_word(char *str)
{
	char	quote;

	str = skip_space(str);
	quote = update_quote_status('\0', *str);
	while (*str && (!is_charset(*str, "| ><") || quote != '\0'))
	{
		str++;
		quote = update_quote_status(quote, *str);
	}
	str = skip_space(str);
	return (str);
}

char	*get_next_pipe(char *str)
{
	if (!str || !*str)
		return (NULL);
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
