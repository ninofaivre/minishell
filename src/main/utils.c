/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:58:59 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/15 13:28:59 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	word_len(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] && str[len] != ' ' && str[len] != ';' && str[len] != '|')
		len++;
	return (len);
}

char	*skip_space(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (str);
}

void	update_cote_status(bool *simplecote, bool *doublecote, char c)
{
	if (c == '"')
	{
		if (*doublecote == true)
			*doublecote = false;
		else if (*simplecote == false)
			*doublecote = true;
	}
	if (c == '\'')
	{
		if (*simplecote == true)
			*simplecote = false;
		else if (*doublecote == false)
			*simplecote = true;
	}
}