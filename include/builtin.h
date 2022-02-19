/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:04:03 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/19 23:10:59 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int		builtin_exit(t_var *var, int status, bool is_child);
void	exit_clean(t_var *var);

int		builtin_pwd(void);
char	*get_pwd(void);

int		builtin_cd(char **argv, char ***env, char ***export_history);

int		builtin_echo(char **argv);

int		builtin_export(char **argv, char ***env, char ***export_history);
void	free_replaced_export(char **export_history, char *argv);
bool	export_parse(char *str);
bool	add_one_var(char ***env, char *str);

int		builtin_unset(char **argv, char ***env, char ***export_history);
bool	unset_one_var_error(char **new_env, char **new_export_history);
void	replace_old_export_history(char ***export_history,
			char **new_export_history, char *name);

bool	exist_in_export_history(char **export_history, char *argv);
bool	comp_export_history_var(char *str1, char *str2);

int		builtin_env(char **argv, char **env);
bool	comp_env_var_name(char *env_var, char *name);
char	**search_in_env(char *name, char **env);

#endif