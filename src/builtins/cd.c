/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:19:49 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/23 22:04:10 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "minishell_error.h"
#include <unistd.h>
#include <errno.h>

int	cd(char **argv)
{
	if (str_tab_len(argv) > 2)
	{
		minishell_error("cd", MAXARG);
		return (1);
	}
	if (chdir(argv[1]) == -1)
	{
		if (errno == ENOTDIR)
			minishell_error("cd",  NOTDIR);
		else
			minishell_error("cd", INACCESSIBLE);
		return (1);
	}
	else
		return (0);
}
