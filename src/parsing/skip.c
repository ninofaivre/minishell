/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 16:16:10 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/30 16:18:23 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*skip_space(char *str)
{
	if (!str)
		return ((char *) NULL);
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
