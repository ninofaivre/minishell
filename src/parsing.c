/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:03:01 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/13 14:02:09 by nfaivre          ###   ########.fr       */
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

// malloc toutes les lists et set list à NULL par défaut
// renvoie un pointeur sur le début de list résultant ou
// renvoie le résultat de free_list s'il y a une erreur de malloc
static t_lists	*init_lists(int n_lists)
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

/*
char	*init_output(char *input)
{
	char	*output;
	int		to_malloc;

	output = (char *) NULL;
	to_malloc = 0;
	while (*input && *input != ';' && *input != '|')
	{
		if (*input == '>')
		{
			input++;
			if (*input == '>')
				input++;
			while (*input == ' ')
				input++;
			while (*(input + to_malloc) && *(input + to_malloc) != ';' && *(input + to_malloc) != '|' && *(input + to_malloc) != ' ')
				to_malloc++;
			break ;
		}
		input++;
	}
	if (to_malloc)
	{
		output = (char *)malloc(sizeof(char) * (to_malloc + 1));
		if (!output)
			return ((char *)-1);
		cpy(output, input, to_malloc);
	}
	return (output);
}
*/

// renvoie le nombre de lists (séparées par des ';')
// 0 s'il n'y a rien ou que des whitespaces et
// -1 s'il y a des erreurs de ';' (rien ou seulement des whitespaces avant un ';')
static int	size_lists(char *input)
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
		while (*input && *input == ' ')
			input++;
		if (*input && *input != ';')
			n_lists++;
		if (*input == ';')
			return (-1);
		while (*input && *input != ';')
			input++;
	}
	return (n_lists);
}

// renvoie le nombre de list (séparés par des '|')
// -1 s'il y a des erreurs de '|' avec aucune commande
// avant le prochain '|' ou ';'
static int	size_list(char *input)
{
	int	n_list;

	n_list = 0;
	while (*input && *input == ' ')
		input++;
	if (*input == '|')
		return (-1);
	if (*input)
		n_list++;
	while (*input && *input != '|' && *input != ';')
		input++;
	if (*input == '|' && !*(input + 1))
		return (-1);
	while (*input && *input != ';')
	{
		if (*input == '|')
			input++;
		while (*input && *input == ' ')
			input++;
		if (*input && *input != ';' && *input != '|')
			n_list++;
		if (*input == ';' || *input == '|' || !input)
			return (-1);
		while (*input && *input != ';' && *input != '|')
			input++;
	}
	return (n_list);
}

t_lists	*build_lists(char *input)
{
	int		j;
	int		i;
	t_lists	*lists;

	j = size_lists(input);
	i = 0;
	if (j == -1)
		write(2, "syntax error after unexpected symbol \";\" \n", 42);
	if (j <= 0)
		return ((t_lists *) NULL);
	while (i < j)
	{
		if (size_list(input) == -1)
			write(2, "syntax error after unexpected symbol \"|\" \n", 42);
		if (size_list(input) <= 0)
			return ((t_lists *) NULL);
		printf("Il y a %i command dans la list %i.\n", size_list(input), i);
		while (*input && *input != ';')
			input++;
		if (*input)
			input++;
		i++;
	}
	lists = init_lists(j);
	return (lists);
}
