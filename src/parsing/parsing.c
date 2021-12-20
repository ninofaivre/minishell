/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:03:01 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/20 14:25:14 by nfaivre          ###   ########.fr       */
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
				free_tab_str(lists->list->input);
			if (lists->list->output)
				free_tab_str(lists->list->output);
			if (lists->list->argv)
				free_tab_str(lists->list->argv);
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
	bool	single_quote;
	bool	double_quote;
	t_lists	*ptr_lists;
	t_list	*ptr_list;

	single_quote = false;
	double_quote = false;
	ptr_lists = lists;
	update_cote_status(&single_quote, &double_quote, *input);
	while (lists)
	{
		if (*input == ';')
		{
			input++;
			update_cote_status(&single_quote, &double_quote, *input);
		}
		ptr_list = lists->list;
		while (lists->list)
		{
			if (*input == '|')
			{
				input++;
				update_cote_status(&single_quote, &double_quote, *input);
			}
			lists->list->output = get_output_input(input, '>');
			lists->list->input = get_output_input(input, '<');
			lists->list->argv = get_argv(input);
			if (lists->list->next)

				while (*input && (*input != '|' || (single_quote == true || double_quote == true)))
				{
					input++;
					update_cote_status(&single_quote, &double_quote, *input);
				}
			lists->list = lists->list->next;
		}
		lists->list = ptr_list;
		if (lists->next)
			while (*input && (*input != ';' || (single_quote == true || double_quote == true)))
			{
				input++;
				update_cote_status(&single_quote, &double_quote, *input);
			}
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
