/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:04:03 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/28 18:09:07 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

void	builtin_exit(bool error, char **env, t_list *list);

int		builtin_pwd(void);
char	*get_pwd(void);

int		builtin_cd(char **argv, char ***env);

int		builtin_echo(char **argv);

int		builtin_export(char **argv, char ***env);
int		builtin_unset(char **argv, char ***env);
int		builtin_env(char **argv, char **env);

#endif