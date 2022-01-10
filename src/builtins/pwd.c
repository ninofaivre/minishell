/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 10:36:05 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/10 10:56:32 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	pwd(void)
{
	int		to_malloc;
	char	*buffer;

	to_malloc = 0;
	buffer = (char *) NULL;
	while (!buffer)
	{
		to_malloc++;
		buffer = (char *)malloc(sizeof(char) * (to_malloc + 1));
		if (!buffer)
			return (-1);
		else if (!getcwd(buffer, to_malloc))
		{
			free (buffer);
			buffer = (char *) NULL;
		}
	}
	printf("%s\n", buffer);
	free(buffer);
	return (0);
}
