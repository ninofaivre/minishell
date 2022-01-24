/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:31:08 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/24 18:57:29 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "global.h"
# include <unistd.h>
# include <sys/types.h>

int		execution(t_var *var);
int		function(t_var *var, int *read_pipe, int *write_pipe);

char	*str_dupe(char *str);
void	write_str_tab_to_fd(char **str_tab, int fd);
char	**ft_split(char const *s, char c);
pid_t	test_fork(t_var *var, char *executable, int *read_pipe, int *write_pipe);
int		builtin(t_var *var, int *read_pipe);
void	take_input(t_redirection *input, int *read_pipe);
void	take_output(t_redirection *output, int *write_pipe);
int		check_builtin(t_var *var);

#endif