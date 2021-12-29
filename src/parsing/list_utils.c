/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:05:56 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/29 23:42:09 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

static void	feel_data(t_list *list, char **env, char *input)
{
	list->output = get_redirection(env, input, '>');
	list->input = get_redirection(env, input, '<');
	list->argv = get_argv(env, input);
}

t_list	*init_list(char *input, char **env)
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
	feel_data(list, env, input);
	list->next = (t_list *) NULL;
	while (n_list--)
	{
		list->next = (t_list *)malloc(sizeof(t_list));
		if (!list->next)
			return ((t_list *) NULL);
		list = list->next;
		input = get_next_pipe(input);
		feel_data(list, env, input);
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
		if (is_charset(*input, "><"))
			input += 1 + (input[1] == *input);
		if (*input == '|')
		{
			input++;
			n_list++;
		}
		input = skip_word(input);
	}
	return (n_list);
}
