/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:03:01 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/23 16:38:34 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

bool	minishell_error(char *error, char *str, char c)
{
	write(2, "minishell : ", 12);
	while (*error)
	{
		if (*error == '#')
			write(2, &c, 1);
		else if (*error == '$')
			while (str && *str)
				write(2, str++, 1);
		else
			write(2, error, 1);
		error++;
	}
	return (true);
}

// return true et écrit une erreur sur la sortie d'erreur
// s'il y a une erreur de syntaxe dans str, false si-non
bool	parse_error(t_var *var, char *str)
{
	str = skip_space(str);
	if (!str || !*str)
		return (true);
	if (*str == '|')
		return (minishell_error("syntax error near symbol \"#\"\n", NULL, '|'));
	while (*str)
	{
		if (*str == '|')
		{
			str++;
			str = skip_space(str);
			if (!*str || *str == '|')
				return (minishell_error("syntax error near symbol \"#\"\n", NULL, '|'));
		}
		else if (is_charset(*str, "><"))
		{
			str += 1 + (str[1] == *str);
			if (!word_len(var, str))
				return (minishell_error("syntax error near symbol \"#\"\n", NULL, str[-1]));
		}
		str = skip_word(str);
	}
	return (false);
}

t_list	*build_list(t_var *var, char *input)
{
	t_list	*list;

	if (parse_error(var, input))
		return ((t_list *) NULL);
	list = init_list(var, input);
	if (!list)
	{
		write(2, "Malloc Error !\n", 15);
		return ((t_list *) NULL);
	}
	return (list);
}
