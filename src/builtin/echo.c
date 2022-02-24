/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:57:22 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/24 14:40:32 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include <unistd.h>

static void	ft_put_str(char *str)
{
	write(1, str, str_len(str));
}

static bool	is_n_parameter(char *str)
{
	if (!str)
		return (false);
	if (*str == '-')
		str++;
	else
		return (false);
	if (!*str)
		return (false);
	while (*str && *str == 'n')
		str++;
	if (*str)
		return (false);
	else
		return (true);
}

int	builtin_echo(char **argv)
{
	bool	backslash_n;

	backslash_n = true;
	argv++;
	if (is_n_parameter(*argv))
	{
			backslash_n = false;
			argv++;
	}
	while (*argv)
	{
		ft_put_str(*argv);
		if (argv[1])
			ft_put_str(" ");
		argv++;
	}
	if (backslash_n == true)
		ft_put_str("\n");
	return (0);
}
