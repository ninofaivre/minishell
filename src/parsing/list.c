/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:05:56 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/25 19:22:29 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

t_redirection	*free_redirection(t_redirection *redirection)
{
	int	i;

	i = 0;
	if (!redirection)
		return (NULL);
	while (redirection[i].content)
	{
		free(redirection[i].content);
		i++;
	}
	free(redirection);
	return (NULL);
}

t_list	*free_list(t_list *list)
{
	t_list	*ptr_list;

	while (list)
	{
		if (list->redirection)
			free_redirection(list->redirection);
		if (list->argv)
			free_str_tab(&list->argv);
		if (list->heredoc)
			free_str_tab(&list->heredoc);
		ptr_list = list;
		list = list->next;
		free(ptr_list);
	}
	return (NULL);
}

static bool	feel_data(t_list *list, char *input)
{
	list->redirection = get_redirection(input);
	list->argv = get_argv(input);
	list->heredoc = NULL;
	if (!list->redirection || !list->argv
		|| get_heredoc(list->redirection, &(list->heredoc)))
		return (true);
	else
		return (false);
}

t_list	*build_list(char *input)
{
	t_list	*ptr_list;
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	ptr_list = list;
	list->next = NULL;
	if (feel_data(list, input))
		return (free_list(ptr_list));
	while (*get_next_pipe(input))
	{
		list->next = malloc(sizeof(t_list));
		if (!list->next)
			return (free_list(ptr_list));
		list = list->next;
		list->next = NULL;
		input = get_next_pipe(input);
		if (feel_data(list, input))
			return (free_list(ptr_list));
	}
	return (ptr_list);
}
