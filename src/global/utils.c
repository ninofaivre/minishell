/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:00:41 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/19 18:17:15 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include <unistd.h>

char	*env_var_value(char **env, char *str)
{
	int	i;

	if (!str || *str != '$' || !str[1])
		return ((char *) NULL);
	str++;
	while (*env)
	{
		i = 0;
		while ((*env)[i] && str[i] && (*env)[i] == str[i]
			&& is_env_var_name_allowed(str[i]))
			i++;
		if ((*env)[i] == '=' && is_env_var_name_allowed(str[i]) == false)
			return (&(*env)[i + 1]);
		env++;
	}
	return ((char *) NULL);
}

int	minishell_error(char *call, char *arg, char *error)
{
	write(2, "minishell : ", 12);
	if (call)
	{
		write(2, call, str_len(call));
		write(2, " : ", 3);
	}
	if (arg)
	{
		write(2, "« ", str_len("« "));
		write(2, arg, str_len(arg));
		write(2, " » : ", str_len(" » : "));
	}
	write(2, error, str_len(error));
	write(2, "\n", 1);
	return (0);
}

bool	is_env_var_name_allowed(char c)
{
	if (!c)
		return (false);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (true);
	else
		return (false);
}

bool	is_charset(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (true);
		charset++;
	}
	return (false);
}

int	str_len(char *str)
{
	unsigned int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}
