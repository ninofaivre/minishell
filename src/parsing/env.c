/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/23 13:31:35 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>
#include <stdio.h>

unsigned int	env_var_len(char *env_var)
{
	unsigned int	len;

	len = 0;
	if (!env_var)
		return (0);
	while (env_var[len])
		len++;
	return (len);
}

char	*search_env_var(char **env, char *str)
{
	int	i;

	if (!str || *str != '$' || !str[1])
		return ((char *) NULL);
	str++;
	while (*env)
	{
		i = 0;
		while ((*env)[i] == str[i])
			i++;
		if ((*env)[i] == '=' && is_alnum(str[i]) == false)
			return (&(*env)[i + 1]);
		env++;
	}
	return ((char *) NULL);
}
