/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:31:08 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/28 16:25:27 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "global.h"
# include <unistd.h>
# include <sys/types.h>

int		execution(t_var *var);
int		function(t_var *var, int *read_pipe, int *write_pipe);

int		check_file(t_var *var);
int		check_exec(t_var *var, char **path);

char	*str_dupe(char *str);
void	write_str_tab_to_fd(char **str_tab, int fd);
char	**ft_split(char const *s, char c);
pid_t	test_fork(t_var *var, char **path,
			int *read_pipe, int *write_pipe);
int		builtin(t_var *var, int *read_pipe);
bool	take_redirection(t_redirection *redirection, int *read_pipe, int *write_pipe);
int		check_builtin(char *str);

#endif