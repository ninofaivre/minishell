/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:03:01 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/25 21:23:57 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell_error.h"
#include <unistd.h>
#include <stdlib.h>

t_list	*parse(t_var *var, char *input)
{
	char	*expanded_input;
	t_list	*list;

	if (parse_error(input, var->minishell_env))
		return (NULL);
	expanded_input = expand_doll(input, var->status, var->minishell_env);
	if (!expanded_input)
	{
		minishell_error("parsing", NULL, ALLOC);
		return (NULL);
	}
	list = build_list(expanded_input);
	free(expanded_input);
	if (!list)
	{
		minishell_error("parsing", NULL, ALLOC);
		return (NULL);
	}
	return (list);
}
