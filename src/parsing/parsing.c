/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:03:01 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/21 20:47:05 by nfaivre          ###   ########.fr       */
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
			free_tab_str(list->input);
		if (list->output)
			free_tab_str(list->output);
		if (list->argv)
			free_tab_str(list->argv);
		ptr_list = list;
		list = list->next;
		free(ptr_list);
	}
	return ((t_list *) NULL);
}

static void	feel_data_list(char *input, t_list *list)
{
	t_quote	quote;
	t_list	*ptr_list;

	quote = init_quote();
	ptr_list = list;
	update_quote_status(&quote, *input);
	while (list)
	{
		if (*input == '|')
		{
			input++;
			update_quote_status(&quote, *input);
		}
		list->output = get_output_input(input, '>');
		list->input = get_output_input(input, '<');
		list->argv = get_argv(input);
		while (*input && (*input != '|' || quote.status == true))
		{
			input++;
			update_quote_status(&quote, *input);
		}
		list = list->next;
	}
	list = ptr_list;
}

t_list	*build_list(char *input)
{
	int		j;
	t_list	*list;

	j = size_list(input);
	if (j == -1)
		write(2, "syntax error after unexpected symbol \"|\" \n", 42);
	if (j <= 0)
		return ((t_list *) NULL);
	list = init_list(input);
	if (!list)
	{
		write(2, "Malloc Error !\n", 15);
		return ((t_list *) NULL);
	}
	feel_data_list(input, list);
	return (list);
}
