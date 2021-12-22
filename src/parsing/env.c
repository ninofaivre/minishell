/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/22 18:03:26 by nfaivre          ###   ########.fr       */
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
	int	j;

	j = 0;
	str++;
	if (!str)
		return ((char *) NULL);
	while (env[j])
	{
		i = 0;
		while (env[j][i] == str[i])
			i++;
		if (env[j][i] == '=' && is_alnum(str[i]) == false)
			break ;
		j++;
	}
	if (env[j])
		return (&env[j][i + 1]);
	else
		return ((char *) NULL);
}
