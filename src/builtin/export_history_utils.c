/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_history_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:04:49 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/19 23:11:42 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	comp_export_history_var(char *str1, char *str2)
{
	str1 += 11;
	while (*str2 && *str2 != '=' && *str1 && *str1 != '=' && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if ((*str2 == '=' || !*str2) && (*str1 == '=' || !*str1))
		return (true);
	else
		return (false);
}

bool	exist_in_export_history(char **export_history, char *argv)
{
	while (*export_history)
	{
		if (comp_export_history_var(*export_history, argv))
			return (true);
		export_history++;
	}
	return (false);
}
