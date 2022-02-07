/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:57:22 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/07 19:44:07 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "global.h"

int	builtin_echo(char **argv)
{
	bool	backslash_n;

	backslash_n = true;
	argv++;
	while (*argv)
	{
		if (is_same_string(*argv, "-n"))
			backslash_n = false;
		else
			printf("%s", *argv);
		if (argv[1])
			printf(" ");
		argv++;
	}
	if (backslash_n == true)
		printf("\n");
	return (0);
}
