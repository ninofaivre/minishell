/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:36:05 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/19 20:26:57 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char	*get_pwd(void)
{
	int		to_malloc;
	char	*buffer;

	to_malloc = 0;
	buffer = NULL;
	while (!buffer)
	{
		to_malloc++;
		buffer = malloc(sizeof(char) * (to_malloc + 1));
		if (!buffer)
			return (NULL);
		else if (!getcwd(buffer, to_malloc))
		{
			free (buffer);
			buffer = NULL;
		}
	}
	return (buffer);
}

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = get_pwd();
	if (!pwd)
	{
		minishell_error("pwd", NULL, ALLOC);
		return (-1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
