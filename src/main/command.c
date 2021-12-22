/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:36:05 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/22 16:39:09 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

/*
int	pwd(void)
{
	int		to_malloc;
	char	*buffer;

	to_malloc = 0;
	buffer = NULL;
	while (!buffer)
	{
		to_malloc++;
		buffer = (char *)malloc(sizeof(char) * (to_malloc + 1));
		if (!buffer)
			return (-1);
		else if (!getcwd(buffer, to_malloc))
		{
			free (buffer);
			buffer = NULL;
		}
	}
	printf("%s\n", buffer);
	free(buffer);
	return (0);
}

int	cd(char *arg_input)
{
	int		i;
	char	*arg;

	i = 0;
	arg = (char *)malloc(sizeof(char) * (word_len(arg_input) + 1));
	if (!arg)
		return (-1);
	while (*arg_input)
	{
		arg[i] = *arg_input;
		arg_input++;
		i++;
	}
	arg[i] = '\0';
	i = chdir(arg);
	free(arg);
	return (i);
}

void	command_not_found(char *command_input)
{
	if (!command_input)
		return ;
	write(2, "minishell: command not found: ", 30);
	while (*command_input && *command_input != ' ')
		write(2, command_input++, 1);
	write(2, "\n", 1);
}
*/
