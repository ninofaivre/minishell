/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:05:56 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/23 15:05:54 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

static void	init_data_one_list(t_list *list)
{
	list->input = (char **) NULL;
	list->output = (char **) NULL;
	list->argv = (char **) NULL;
}

t_list	*init_list(char *input)
{
	t_list	*ptr_list;
	t_list	*list;
	int		n_list;

	n_list = size_list(input);
	list = (t_list *)malloc(sizeof(t_list));
	if (!list || n_list == -1)
		return ((t_list *) NULL);
	n_list--;
	ptr_list = list;
	init_data_one_list(list);
	list->next = (t_list *) NULL;
	while (n_list--)
	{
		list->next = (t_list *)malloc(sizeof(t_list));
		if (!list->next)
			return ((t_list *) NULL);
		list = list->next;
		init_data_one_list(list);
		list->next = (t_list *) NULL;
	}
	return (ptr_list);
}

// renvoie le nombre de maillons de list (séparés par des '|')
// -1 s'il y a des erreurs de '|' avec aucune commande
// avant le prochain '|'
int	size_list(char *input)
{
	int		n_list;

	n_list = 0;
	input = skip_space(input);
	if (*input)
		n_list++;
	while (*input)
	{
		if (*input == '|')
		{
			input++;
			n_list++;
		}
		input = skip_word(input);
	}
	return (n_list);
}
