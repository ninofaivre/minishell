/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:57:22 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/10 11:12:38 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	echo(char **argv)
{
	bool	backslash_n;

	backslash_n = true;
	argv++;
	while (*argv)
	{
		if (*argv[0] == '-' && *argv[1] == 'n' && *argv[2] == '\0')
			backslash_n = false;
		else
			printf("%s ", *argv);
		argv++;
	}
	if (backslash_n == true)
		printf("\n");
	return (0);
}
