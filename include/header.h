/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:31:08 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/24 15:42:12 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>

# ifndef PROMPT
#  define PROMPT "minishell$> "
# endif

char			*search_env_var(char **env, char *str);

int				int_len(int nbr);
bool			is_alnum(char c);
bool			is_charset(char c, char *charset);
unsigned int	str_len(char *str);

char			update_quote_status(char quote, char c);

int				execution(t_var *var);
bool			is_same_string(char *str1, char *str2);
int				count_char_in_str(char *str, char c);
int				function(t_var *var, int *read_pipe, int *write_pipe);

int				ft_pwd(void);
char			*get_pwd(void);
int				cd(char **argv, char ***env);
int				echo(char **argv);
int				ft_export(char **argv, char ***env);
int				unset(char **argv, char ***env);
int				ft_env(char **argv, char **env);
char			*str_dupe(char *str);
void			write_str_tab_to_fd(char **str_tab, int fd);
char			**ft_split(char const *s, char c);
pid_t			test_fork(t_var *var, char *executable, int *read_pipe, int *write_pipe);
int				builtin(t_var *var, int *read_pipe);
char			*concat(char *str1, char *str2);

#endif