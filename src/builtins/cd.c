/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:19:49 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/14 12:38:52 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>
#include <errno.h>

int	cd(char **argv)
{
	if (str_tab_len(argv) > 2)
	{
		minishell_error("cd: too much args\n", (char *)NULL, '\0');
		return (1);
	}
	if (chdir(argv[1]) == -1)
	{
		if (errno == ENOTDIR)
			minishell_error("cd : $ is not a directory\n", argv[1], '\0');
		else
			minishell_error("cd : unable to open this directory\n", (char *)NULL, '\0');
		return (1);
	}
	else
		return (0);
}
