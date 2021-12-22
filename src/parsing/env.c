/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/22 17:03:20 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

unsigned int	env_var_len(char *env_var)
{
	unsigned int	len;

	len = 0;

	while (env_var && env_var[len])
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
		if (i == 1)
			printf("%c = %c\n", *env[i], str[i]);
		if (env[j][i] == '=' && !((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9')))
			break ;
		j++;
	}
	return (&env[j][i + 1]);
}
