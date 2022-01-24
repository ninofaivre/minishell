/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:03:01 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/24 17:45:45 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell_error.h"
#include <unistd.h>

static bool	parse_error(t_var *var, char *str)
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

t_list	*parse(t_var *var, char *input)
{
	t_list	*list;

	if (!parse_error(var, input))
		return ((t_list *) NULL);
	list = build_list(var, input);
	if (!list)
		minishell_error("parsing", ALLOC);
	return (list);
}
