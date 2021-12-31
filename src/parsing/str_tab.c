/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:42:00 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/31 14:26:53 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

void	free_redirection(t_redirection *redirection)
{
	int	i;

	i = 0;
	if (!redirection)
		return ;
	while (redirection[i].content)
	{
		free(redirection[i].content);
		i++;
	}
	free(redirection);
}

void	free_tab_str(char **str_tab)
{
	int	i;

	i = 0;
	if (!str_tab)
		return ;
	while (str_tab[i])
	{
		free(str_tab[i]);
		i++;
	}
	free(str_tab);
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
		free_tab_str(str_tab);
		return ((char **) NULL);
	}
	while (str_tab && str_tab[i])
	{
		new_str_tab[i] = str_tab[i];
		i++;
	}
	if (str_tab)
		free(str_tab);
	new_str_tab[i] = str;
	new_str_tab[i + 1] = (char *) NULL;
	return (new_str_tab);
}
