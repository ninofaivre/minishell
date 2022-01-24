/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:29:34 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/24 17:41:40 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include <stdlib.h>

char	*str_dupe(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!str)
		return ((char *) NULL);
	new_str = (char *)malloc(sizeof(char) * (str_len(str) + 1));
	if (!new_str)
		return ((char *) NULL);
	while (*str)
		new_str[i++] = *str++;
	new_str[i] = '\0';
	return (new_str);
}

char	*concat(char *str1, char *str2)
{
	int		i;
	char	*new_str;

	i = str_len(str1) + str_len(str2) + 1;
	new_str = (char *)malloc(sizeof(char) * (i));
	i = 0;
	if (!new_str)
		return ((char *) NULL);
	while (str1 && *str1)
		new_str[i++] = *str1++;
	while (str2 && *str2)
		new_str[i++] = *str2++;
	new_str[i] = '\0';
	return (new_str);
}

bool	is_same_string(char *str1, char *str2)
{
	if ((!str1 && str2) || (str1 && !str2))
		return (false);
	else if (!str1 && !str2)
		return (true);
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (true);
	else
		return (false);
}

int	count_char_in_str(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}
