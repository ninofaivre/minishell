/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:36:05 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/24 11:00:43 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

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
