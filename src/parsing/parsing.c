/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:03:01 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/01 17:32:40 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell_error.h"
#include <unistd.h>

static bool	parse_error(t_var *var, char *str)
{
	str = skip_space(str);
	if (!str || !*str)
		return (true);
	if (*str == '|')
		return (minishell_error("parsing", NULL, VOIDPIPE) + true);
	while (*str)
	{
		if (*str == '|')
		{
			str++;
			str = skip_space(str);
			if (!*str || *str == '|')
				return (minishell_error("parsing", NULL, VOIDPIPE) + true);
		}
		else if (is_charset(*str, "><"))
		{
			str += 1 + (str[1] == *str);
			if (!word_len(var, str) && str[-1] == '<')
				return (minishell_error("parsing", NULL, VOIDINPUT) + true);
			else if (!word_len(var, str) && str[-1] == '>')
				return (minishell_error("parsing", NULL, VOIDOUTPUT) + true);
		}
		str = skip_word(str);
	}
	return (false);
}

t_list	*parse(t_var *var, char *input)
{
	t_list	*list;

	if (parse_error(var, input))
		return ((t_list *) NULL);
	list = build_list(var, input);
	if (!list)
	{
		minishell_error("parsing", (char *) NULL, ALLOC);
		return ((t_list *) NULL);
	}
	return (list);
}
