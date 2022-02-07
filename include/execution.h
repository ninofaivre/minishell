/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:31:08 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/07 17:00:39 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "global.h"
# include <unistd.h>
# include <sys/types.h>

int		execution(t_var *var);
int		function(t_var *var, int *read_pipe, int *write_pipe);
void	free_pipes(int **pipes);

int		check_file(t_var *var);
int		check_exec(t_var *var, char **path);

int		count_list(t_var *var);

void	write_str_tab_to_fd(char **str_tab, int fd);
void	close_pipe(int *pipe);
char	**ft_split(char const *s, char c);
pid_t	test_fork(t_var *var, char **path,
			int *read_pipe, int *write_pipe);
bool	need_a_child(char *argv_0);
int		builtin_child(t_var *var);
int		builtin_main(t_var *var);
bool	is_builtin(char *argv_0);

bool	take_redirection(t_redirection *redirection, int *read_pipe,
			int *write_pipe, bool is_child);
int		take_input(char *content, bool is_double, int fd_input);
int		take_output(char *content, bool is_double, int fd_output);

void	pipe_error(char *call, char *arg);

#endif