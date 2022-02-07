/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:04:03 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/07 14:55:38 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

int		builtin_exit(char **env, t_list *list, int status, bool is_child);
void	exit_clean(char **env, t_list *list);

int		builtin_pwd(void);
char	*get_pwd(void);

int		builtin_cd(char **argv, char ***env);

int		builtin_echo(char **argv);

int		builtin_export(char **argv, char ***env);
int		builtin_unset(char **argv, char ***env);
int		builtin_env(char **argv, char **env);
bool	comp_env_var_name(char *env_var, char *name);
char	**search_in_env(char *name, char **env);

#endif