/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:04:03 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/20 16:01:10 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "global.h"

int		builtin_exit(t_var *var, int status, bool is_child);
void	exit_clean(t_var *var);

int		builtin_pwd(void);
char	*get_pwd(void);

int		builtin_cd(char **argv, t_env *env);

int		builtin_echo(char **argv);

int		builtin_export(char **argv, t_env *minishell_env);

int		builtin_unset(char **argv, t_env *minishell_env);

bool	exist_in_export_history(char **export_history, char *argv);
bool	comp_export_history_var(char *str1, char *str2);

int		builtin_env(char **argv, t_env *minishell_env);
bool	comp_env_var_name(char *env_var, char *name);
char	**search_in_env(char *name, char **env);

#endif