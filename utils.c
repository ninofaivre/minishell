/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:58:59 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/24 10:44:39 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*skip_whitespace(char *str)
{
	if (!str)
		return (NULL);
	while (*str && *str == ' ')
		str++;
	if (!*str)
		return (NULL);
	else
		return (str);
}

char	*skip_word(char *str)
{
	if (!str)
		return (NULL);
	while (*str && *str != ' ')
		str++;
	if (!*str)
		return (NULL);
	else
		return (str);
}

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
