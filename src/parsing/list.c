/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:05:56 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/28 16:32:49 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

t_redirection	*free_redirection(t_redirection *redirection)
{
	int	i;

	i = 0;
	if (!redirection)
		return ((t_redirection *) NULL);
	while (redirection[i].content)
	{
		free(redirection[i].content);
		i++;
	}
	free(redirection);
	return ((t_redirection *) NULL);
}

t_list	*free_list(t_list *list)
{
	t_list	*ptr_list;

	while (list)
	{
		if (list->redirection)
			free_redirection(list->redirection);
		if (list->argv)
			free_str_tab(list->argv);
		ptr_list = list;
		list = list->next;
		free(ptr_list);
	}
	return ((t_list *) NULL);
}

static bool	feel_data(t_var *var, t_list *list, char *input)
{
	list->redirection = get_redirection(var, input);
	list->argv = get_argv(var, input);
	if (!list->redirection || !list->argv)
		return (false);
	else
		return (true);
}

t_list	*build_list(t_var *var, char *input)
{
	t_list	*ptr_list;
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return ((t_list *) NULL);
	ptr_list = list;
	list->next = (t_list *) NULL;
	if (feel_data(var, list, input) == false)
		return (free_list(ptr_list));
	while (*get_next_pipe(input))
	{
		list->next = (t_list *)malloc(sizeof(t_list));
		if (!list->next)
			return (free_list(ptr_list));
		list = list->next;
		list->next = (t_list *) NULL;
		input = get_next_pipe(input);
		if (feel_data(var, list, input) == false)
			return (free_list(ptr_list));
	}
	return (ptr_list);
}
