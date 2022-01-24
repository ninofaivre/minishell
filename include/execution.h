/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:31:08 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/24 17:05:37 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

int				execution(t_var *var);
bool			is_same_string(char *str1, char *str2);
int				count_char_in_str(char *str, char c);
int				function(t_var *var, int *read_pipe, int *write_pipe);

char			*str_dupe(char *str);
void			write_str_tab_to_fd(char **str_tab, int fd);
char			**ft_split(char const *s, char c);
pid_t			test_fork(t_var *var, char *executable, int *read_pipe, int *write_pipe);
int				builtin(t_var *var, int *read_pipe);
char			*concat(char *str1, char *str2);

#endif