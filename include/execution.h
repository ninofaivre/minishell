/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:31:08 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/03 22:08:09 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "global.h"
# include <unistd.h>

int		execution(t_var *var);
int		wait_childs(int pid, t_var *var);
void	free_pipes(int **pipes);

int		builtin_child(t_var *var);
int		builtin_main(t_var *var);
bool	is_builtin(char *argv_0);
bool	need_a_child(char **argv);

int		exec_file(t_var *var);
int		exec_cmd(t_var *var, char **path);

pid_t	fork_cmd(t_var *var, char **path,
			int *read_pipe, int *write_pipe);
int		call_fork_cmd(t_var *var, int *read_pipe, int *write_pipe);

bool	take_redirection(t_list *list, int *read_pipe,
			int *write_pipe, bool is_child);

int		take_heredoc(char **heredoc, int *read_pipe);
int		take_input(char *content, int fd_input);
int		take_output(char *content, bool is_double, int fd_output);

char	**ft_split(char const *s, char c);

int		count_list(t_var *var);
void	write_str_tab_to_fd(char **str_tab, int fd);
void	close_pipe(int *pipe);
void	pipe_error(char *call, char *arg);

#endif