/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/22 15:49:49 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	env_var_len(char *env_var)
{
	unsigned int	len;
	
	if (!env_var)
		return (0);
	while (*env_var != '=')
		env_var++;
	while (env_var[len])
		len++;
	return (len);
}

char	*search_env_var(char **env, char *str)
{
	int	i;

	i = 0;
	while (*env)
	{
		while (*env[i] == str[i])
			i++;
		if (env[i] == '=')
			break ;
		env++;
	}
	return (*env);
}
