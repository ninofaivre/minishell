/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:03:01 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/23 20:34:44 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "minishell_error.h"
#include <stdlib.h>

int	minishell_error(char *call, char *error)
{
	write(2, "minishell : ", 12);
	if (call)
	{
		write(2, call, str_len(call));
		write(2, " : ", 3);
	}
	write(2, error, str_len(error));
	write(2, "\n", 1);
	return (0);
}

bool	parse_error(t_var *var, char *str)
{
	str = skip_space(str);
	if (!str || !*str)
		return (false);
	if (*str == '|')
		return ((bool)minishell_error("parsing", VOIDPIPE));
	while (*str)
	{
		if (*str == '|')
		{
			str++;
			str = skip_space(str);
			if (!*str || *str == '|')
				return ((bool)minishell_error("parsing", VOIDPIPE));
		}
		else if (is_charset(*str, "><"))
		{
			str += 1 + (str[1] == *str);
			if (!word_len(var, str) && str[-1] == '<')
				return ((bool)minishell_error("parsing", VOIDINPUT));
			else if (!word_len(var, str) && str[-1] == '>')
				return ((bool)minishell_error("parsing", VOIDOUTPUT));
		}
		str = skip_word(str);
	}
	return (true);
}

t_list	*build_list(t_var *var, char *input)
{
	t_list	*list;

	if (!parse_error(var, input))
		return ((t_list *) NULL);
	list = init_list(var, input);
	if (!list)
		minishell_error("parsing", ALLOC);
	return (list);
}
