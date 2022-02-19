/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:48:57 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/19 20:27:03 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

bool	comp_env_var_name(char *env_var, char *name)
{
	while (*env_var && *name && *env_var == *name)
	{
		env_var++;
		name++;
	}
	if (*env_var == '=' && !*name)
		return (true);
	else
		return (false);
}

char	**search_in_env(char *name, char **env)
{
	int	i;

	while (*env)
	{
		i = 0;
		while ((*env)[i] == name[i] && (*env)[i] && name[i] && name[i] != '=')
			i++;
		if ((!name[i] || name[i] == '=') && (*env)[i] == '=')
			return (&(*env));
		env++;
	}
	return (NULL);
}
