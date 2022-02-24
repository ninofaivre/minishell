/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:03:01 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/23 15:24:10 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell_error.h"
#include <unistd.h>

t_list	*parse(t_var *var, char *input)
{
	t_list	*list;

	if (parse_error(var, input))
		return (NULL);
	list = build_list(var, input);
	if (!list)
	{
		minishell_error("parsing", NULL, ALLOC);
		return (NULL);
	}
	return (list);
}
