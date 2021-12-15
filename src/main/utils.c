/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:58:59 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/15 15:42:47 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	word_len(char *str)
{
	bool	single_quote;
	bool	double_quote;
	int		len;

	single_quote = false;
	double_quote = false;
	len = 0;
	if (!str)
		return (0);
	str = skip_space(str);
	if (*str == '\'' || *str == '"')
		str++;
	while (str[len] && str[len] != ';' && str[len] != '|' && (str[len] != ' ' || single_quote == true || double_quote == true))
	{
		update_cote_status(&single_quote, &double_quote, str[len]);
		len++;
	}
	return (len);
}

char	*skip_space(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (str);
}

void	update_cote_status(bool *single_quote, bool *double_quote, char c)
{
	if (c == '"')
	{
		if (*double_quote == true)
			*double_quote = false;
		else if (*single_quote == false)
			*double_quote = true;
	}
	if (c == '\'')
	{
		if (*single_quote == true)
			*single_quote = false;
		else if (*double_quote == false)
			*single_quote = true;
	}
}