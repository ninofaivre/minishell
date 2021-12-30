/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:05:56 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/30 10:35:33 by nfaivre          ###   ########.fr       */
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
