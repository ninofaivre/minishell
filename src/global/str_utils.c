/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:29:34 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/20 17:37:53 by nfaivre          ###   ########.fr       */
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
		return (NULL);
	new_str = malloc(sizeof(char) * (str_len(str) + 1));
	if (!new_str)
		return (NULL);
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
	new_str = malloc(sizeof(char) * (i));
	i = 0;
	if (!new_str)
		return (NULL);
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

int	str_cmp(char *str1, char *str2)
{
	if (!str1 && !str2)
		return (0);
	else if (!str1)
		return (-1);
	else if (!str2)
		return (1);
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

void	str_ncpy(char *dest, char *src, int n_char)
{
	int	i;

	i = 0;
	if (!src || !dest)
		return ;
	while (i < n_char && src[i])
	{
		dest[i] = src[i];
		i++;
	}
}
