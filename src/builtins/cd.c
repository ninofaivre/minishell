/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:19:49 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/10 10:51:56 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <unistd.h>
#include <errno.h>

void	cd(char **argv)
{
	if (str_tab_len(argv) > 2)
	{
		minishell_error("cd: $ too much args\n", (char *)NULL);
		return (1);
	}
	if (chdir(argv[1]) == -1)
	{
		if (errno == ENOTDIR)
			minishell_error("cd : $ is not a directory\n", argv[1]);
		else
			minishell_error("cd : unable to open this directory\n", (char *)NULL);
		return (1);
	else
		return (0);
}
