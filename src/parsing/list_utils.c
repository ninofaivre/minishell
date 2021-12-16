/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:05:56 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/16 15:19:41 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

static void	init_data_one_list(t_list *list)
{
	list->input = (char **) NULL;
	list->output = (char **) NULL;
	list->command = (char *) NULL;
	list->arg = (char **) NULL;
}

// malloc toutes les lists et set list à NULL par défaut
// renvoie un pointeur sur le début de list résultant ou
// renvoie le résultat de free_list s'il y a une erreur de malloc
t_lists	*init_lists(int n_lists)
{
	t_lists	*ptr_lists;
	t_lists	*lists;

	ptr_lists = (t_lists *) NULL;
	lists = (t_lists *) NULL;
	lists = (t_lists *)malloc(sizeof(t_lists));
	if (!lists)
		return ((t_lists *) NULL);
	lists->list = (t_list *) NULL;
	lists->next = (t_lists *) NULL;
	ptr_lists = lists;
	n_lists--;
	while (n_lists--)
	{
		lists->next = (t_lists *)malloc(sizeof(t_lists));
		lists = lists->next;
		if (!lists)
			return (free_lists(ptr_lists));
		lists->list = (t_list *) NULL;
		lists->next = (t_lists *) NULL;
	}
	return (ptr_lists);
}

int	init_list(t_lists *lists, char *input)
{
	t_lists	*ptr_lists;
	t_list	*ptr_list;
	int		n_list;

	ptr_lists = lists;
	while (lists)
	{
		n_list = size_list(input);
		lists->list = (t_list *)malloc(sizeof(t_list));
		if (!lists->list || n_list == -1)
			return (-1);
		n_list--;
		ptr_list = lists->list;
		init_data_one_list(lists->list);
		lists->list->next = (t_list *) NULL;
		while (n_list--)
		{
			lists->list->next = (t_list *)malloc(sizeof(t_list));
			if (!lists->list)
				return (-1);
			lists->list = lists->list->next;
			init_data_one_list(lists->list);
			lists->list->next = (t_list *) NULL;
		}
		lists->list = ptr_list;
		lists = lists->next;
		while (*input && *input != ';')
			input++;
		if (*input == ';')
			input++;
	}
	lists = ptr_lists;
	return (0);
}

// renvoie le nombre de lists (séparées par des ';')
// 0 s'il n'y a rien ou que des whitespaces et
// -1 s'il y a des erreurs de ';' (rien ou seulement des whitespaces avant un ';')
int	size_lists(char *input)
{
	int	n_lists;

	n_lists = 0;
	while (*input && *input == ' ')
		input++;
	if (*input == ';')
		return (-1);
	if (*input)
		n_lists++;
	while (*input && *input != ';')
		input++;
	while (*input)
	{
		if (*input == ';')
			input++;
		input = skip_space(input);
		if (*input && *input != ';')
			n_lists++;
		if (*input == ';')
			return (-1);
		while (*input && *input != ';')
			input++;
	}
	return (n_lists);
}

// renvoie le nombre de maillons de list (séparés par des '|')
// -1 s'il y a des erreurs de '|' avec aucune commande
// avant le prochain '|' ou ';'
int	size_list(char *input)
{
	int	n_list;

	n_list = 0;
	input = skip_space(input);
	if (*input == '|')
		return (-1);
	if (*input)
		n_list++;
	while (*input && *input != '|' && *input != ';')
		input++;
	while (*input && *input != ';')
	{
		if (*input == '|')
			input++;
		input = skip_space(input);
		if (*input && *input != ';' && *input != '|')
			n_list++;
		if (*input == ';' || *input == '|' || !*input)
			return (-1);
		while (*input && *input != ';' && *input != '|')
			input++;
	}
	return (n_list);
}