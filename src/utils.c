/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:58:59 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/13 11:17:19 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

bool	comp_one_word(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (false);
	while (*str1 != ' ' && *str1 == *str2 && *str1 && *str2)
	{
		str1++;
		str2++;
	}
	if (*str2 || (*str1 != ' ' && *str1))
		return (false);
	else
		return (true);
}

int	word_len(char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] && str[len] != ' ')
		len++;
	return (len);
}
