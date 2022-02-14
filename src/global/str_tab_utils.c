/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tab_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:42:00 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/14 10:12:55 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include <stdlib.h>
#include <stdio.h>

void	print_str_tab(char **str_tab)
{
	if (!str_tab)
		return ;
	while (*str_tab)
		printf("%s\n", *str_tab++);
}

char	**free_str_tab(char **str_tab)
{
	int	i;

	i = 0;
	if (!str_tab)
		return ((char **) NULL);
	while (str_tab[i])
	{
		free(str_tab[i]);
		i++;
	}
	free(str_tab);
	return ((char **) NULL);
}

int	str_tab_len(char **str_tab)
{
	int	i;

	i = 0;
	if (!str_tab)
		return (0);
	while (str_tab[i])
		i++;
	return (i);
}

char	**add_str_to_str_tab(char **str_tab, char *str)
{
	int		i;
	char	**new_str_tab;

	i = 0;
	new_str_tab = (char **)malloc(sizeof(char *) * (str_tab_len(str_tab) + 2));
	if (!new_str_tab)
	{
		if (str_tab)
			free(str_tab);
		return ((char **) NULL);
	}
	while (str_tab && str_tab[i])
	{
		new_str_tab[i] = str_tab[i];
		i++;
	}
	new_str_tab[i] = str;
	new_str_tab[i + 1] = (char *) NULL;
	if (str_tab)
		free(str_tab);
	return (new_str_tab);
}

void	str_tab_sort(char **export_history)
{
	int		i;
	char	*tmp;

	i = 0;
	while (export_history[i + 1])
	{
		if (str_cmp(export_history[i], export_history[i + 1]) > 0)
		{
			tmp = export_history[i];
			export_history[i] = export_history[i + 1];
			export_history[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}
