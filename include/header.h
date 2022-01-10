/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:31:08 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/10 12:05:11 by nfaivre          ###   ########.fr       */
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

typedef struct s_list
{
	struct s_redirection	*input;
	struct s_redirection	*output;
	char					**argv;
	struct s_list			*next;
}	t_list;

typedef struct s_redirection
{
	char	*content;
	bool	is_double;
}	t_redirection;

char			*search_env_var(char **env, char *str);

t_redirection	*get_redirection(char **env, char *input, char guillemet, int status);
char			**get_argv(char **env, char *input, int status);
char			*get_next_pipe(char *str);

int				add_env_var_to_word(char *word, char *env_var);
int				count_redirection(char *str, char guillemet);

t_list			*init_list(char *input, char **env, int status);
int				size_list(char *input);

t_list			*build_list(char **env, char *input, int status);
t_list			*free_list(t_list *lists);

void			free_redirection(t_redirection *redirection);
void			free_tab_str(char **str_tab);
int				str_tab_len(char **str_tab);
char			**add_str_to_str_tab(char **str_tab, char *str);

char			*itoa(int nbr);
int				int_len(int nbr);
bool			is_alnum(char c);
char			*skip_word(char *str);
char			*skip_space(char *str);
char			*skip_var(char *str);
unsigned int	word_len(char **env, char *str, int status);
bool			is_charset(char c, char *charset);
unsigned int	str_len(char *str);

char			update_quote_status(char quote, char c);

int				execution(t_list *list, char **env);
bool			is_same_string(char *str1, char *str2);

/*
int				pwd(void);
int				cd(char *arg_input);
*/

#endif