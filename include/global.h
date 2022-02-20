/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:34:51 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/20 22:50:42 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include "minishell_error.h"
# include <stdbool.h>

# ifndef PROMPT
#  define PROMPT "minishell$> "
# endif

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_redirection
{
	char	*content;
	bool	is_double;
	char	guillemet;
}	t_redirection;

typedef struct s_list
{
	struct s_redirection	*redirection;
	char					**argv;
	struct s_list			*next;
}	t_list;

typedef struct s_var
{
	struct s_list	*list;
	struct s_list	*ptr_start_list;
	struct s_env	*minishell_env;
	struct s_env	*ptr_start_minishell_env;
	int				**pipes;
	int				status;
}	t_var;

bool	is_charset(char c, char *charset);
int		str_len(char *str);
int		count_char_in_str(char *str, char c);
int		str_chr(char *str, char c);

void	print_str_tab(char **str_tab);
char	**free_str_tab(char ***str_tab);
int		str_tab_len(char **str_tab);
char	**add_str_to_str_tab(char **str_tab, char *str);
void	str_tab_sort(char **export_history);

char	*str_dupe(char *str);
char	*concat(char *str1, char *str2);
bool	is_same_string(char *str1, char *str2);
int		str_cmp(char *str1, char *str2);
void	str_ncpy(char *dest, char *src, int n_char);

t_env	*get_minishell_env(char **env);
void	*free_minishell_env(t_env *minishell_env);
bool	fill_one_minishell_env(t_env *minishell_env, char *str);
char	*get_value_arg(char *str);
void	init_one_minishell_env(t_env *minishell_env);
void	free_one_minishell_env(t_env *minishell_env);

char	*get_env_var_value(t_env *minishell_env, char *name);
bool	is_env_var_name_allowed(char c);
bool	is_existing_in_env(t_env *minishell_env, char *name);
char	**convert_env_in_str_tab(t_env *minishell_env);

#endif