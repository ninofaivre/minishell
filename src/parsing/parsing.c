/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:03:01 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/15 16:29:01 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

// free toutes les lists y compris list et le contenu (input/output/command/arg)
// renvoie (t_lists *) NULL
t_lists	*free_lists(t_lists *lists)
{
	t_lists	*ptr_lists;
	t_list	*ptr_list;

	while (lists)
	{
		while (lists->list)
		{
			if (lists->list->input)
				free(lists->list->input);
			if (lists->list->output)
				free(lists->list->output);
			if (lists->list->command)
				free(lists->list->command);
			if (lists->list->arg)
				free(lists->list->arg);
			ptr_list = lists->list;
			lists->list = lists->list->next;
			free(ptr_list);
		}
		ptr_lists = lists;
		lists = lists->next;
		free(ptr_lists);
	}
	return ((t_lists *) NULL);
}

static void	feel_data_list(char *input, t_lists *lists)
{
	t_lists	*ptr_lists;
	t_list	*ptr_list;

	ptr_lists = lists;
	while (lists)
	{
		if (*input == ';')
			input++;
		ptr_list = lists->list;
		while (lists->list)
		{
			if (*input == '|')
				input++;
			lists->list->output = get_output(input);
			if (lists->list->next)
				while (*input && *input != '|')
					input++;
			lists->list = lists->list->next;
		}
		lists->list = ptr_list;
		if (lists->next)
			while (*input && *input != ';')
				input++;
		lists = lists->next;
	}
	lists = ptr_lists;
}

t_lists	*build_lists(char *input)
{
	int		j;
	t_lists	*lists;

	j = size_lists(input);
	if (j == -1)
		write(2, "syntax error after unexpected symbol \";\" \n", 42);
	if (j <= 0)
		return ((t_lists *) NULL);
	lists = init_lists(j);
	j = init_list(lists, input);
	if (j == -1)
	{
		write(2, "syntax error after unexpected symbol \"|\" \n", 42);
		return ((t_lists *) NULL);
	}
	feel_data_list(input, lists);
	return (lists);
}
