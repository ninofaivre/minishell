/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:03:01 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/29 23:45:17 by nfaivre          ###   ########.fr       */
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

bool	syntax_error(char c)
{
	write(2, "syntax error near symbol \"", 26);
	write(2, &c, 1);
	write(2, "\"\n", 2);
	return (true);
}

// return true et écrit une erreur sur la sortie d'erreur
// s'il y a une erreur de syntaxe dans str, false si-non
bool	parse_error(char **env, char *str)
{
	str = skip_space(str);
	if (*str == '|')
		return (syntax_error('|'));
	while (*str)
	{
		if (*str == '|')
		{
			str++;
			str = skip_space(str);
			if (!*str || *str == '|')
				return (syntax_error('|'));
		}
		else if (is_charset(*str, "><"))
		{
			str += 1 + (str[1] == *str);
			if (!word_len(env, str))
				return (syntax_error(*(str - 1)));
		}
		str = skip_word(str);
	}
	return (false);
}

t_list	*build_list(char **env, char *input)
{
	t_list	*list;

	if (parse_error(env, input) || !size_list(input))
		return ((t_list *) NULL);
	list = init_list(input, env);
	if (!list)
	{
		write(2, "Malloc Error !\n", 15);
		return ((t_list *) NULL);
	}
	return (list);
}
