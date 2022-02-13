/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:34:51 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/13 12:55:48 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# include "minishell_error.h"
# include <stdbool.h>

# ifndef PROMPT
#  define PROMPT "minishell$> "
# endif

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
	char			***env;
	char			***export_history;
	int				**pipes;
	int				status;
}	t_var;

char	*env_var_value(char **env, char *str);
bool	is_env_var_name_allowed(char c);
bool	is_charset(char c, char *charset);
int		str_len(char *str);

void	print_str_tab(char **str_tab);
char	**free_str_tab(char **str_tab);
int		str_tab_len(char **str_tab);
char	**add_str_to_str_tab(char **str_tab, char *str);

char	*str_dupe(char *str);
char	*concat(char *str1, char *str2);
bool	is_same_string(char *str1, char *str2);
int		count_char_in_str(char *str, char c);

#endif