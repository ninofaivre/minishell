/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:20:46 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/26 10:47:09 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "global.h"

t_list			*parse(t_var *var, char *input);

bool			parse_error(char *str, t_env *minishell_env);

t_redirection	*free_redirection(t_redirection *redirection);
t_list			*free_list(t_list *list);
t_list			*build_list(char *input);

t_redirection	*get_redirection(char *input);
char			**get_argv(char *input);
bool			get_heredoc(t_redirection *redirection, char ***heredoc);

int				add_int_word(char *word, int status);
int				add_str_word(char *word, char *str);

char			*skip_space(char *str);
char			*skip_word(char *str);
char			*get_next_pipe(char *str);

unsigned int	word_len(char *str);
char			update_quote_status(char quote, char c);

char			*expand_doll(char *str, int status, t_env *minishell_env);

#endif