/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:04:03 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/05 01:14:06 by nfaivre          ###   ########.fr       */
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
bool	update_pwd(t_env *minishell_env, bool init);

int		builtin_echo(char **argv);

int		builtin_export(char **argv, t_env *minishell_env);
bool	manual_export(char *name, char *value, t_env *minishell_env);

bool	is_arg_existing_in_env(t_env *minishell_env, char *arg);
bool	parse_export_arg(char *arg);
void	print_one_export_history(t_env *minishell_env);
char	*find_biggest_name(t_env *minishell_env);
t_env	*find_lowest_name(t_env *minishell_env, t_env	*old_lowest_name);

int		builtin_unset(char **argv, t_var *var);

bool	exist_in_export_history(char **export_history, char *argv);
bool	comp_export_history_var(char *str1, char *str2);

int		builtin_env(char **argv, t_env *minishell_env);
bool	comp_env_var_name(char *env_var, char *name);
char	**search_in_env(char *name, char **env);

#endif