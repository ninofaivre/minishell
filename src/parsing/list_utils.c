/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:05:56 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/30 12:37:28 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

// free toutes list et le contenu (input/output/command/arg)
// renvoie (t_list *) NULL
t_list	*free_list(t_list *list)
{
	t_list	*ptr_list;

	while (list)
	{
		if (list->input)
			free_redirection(list->input);
		if (list->output)
			free_redirection(list->output);
		if (list->argv)
			free_tab_str(list->argv);
		ptr_list = list;
		list = list->next;
		free(ptr_list);
	}
	return ((t_list *) NULL);
}

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

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return ((t_list *) NULL);
	ptr_list = list;
	feel_data(list, env, input);
	list->next = (t_list *) NULL;
	while (*get_next_pipe(input))
	{
		list->next = (t_list *)malloc(sizeof(t_list));
		if (!list->next)
			return (free_list(ptr_list));
		list = list->next;
		input = get_next_pipe(input);
		feel_data(list, env, input);
		list->next = (t_list *) NULL;
	}
	return (ptr_list);
}
