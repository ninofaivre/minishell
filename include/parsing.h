/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:20:46 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/24 17:48:08 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "global.h"

t_list			*parse(t_var *var, char *input);

t_list			*free_list(t_list *list);
t_list			*build_list(t_var *var, char *input);

t_redirection	*get_redirection(t_var *var, char *input, char guillemet);
char			**get_argv(t_var *var, char *input);

int				add_int_word(char *word, int status);
int				add_str_word(char *word, char *str);
int				count_redirection(char *str, char guillemet);

char			*skip_space(char *str);
char			*skip_var(char *str);
char			*skip_word(char *str);
char			*get_next_pipe(char *str);

char			*itoa(int nbr);
unsigned int	word_len(t_var *var, char *str);
char			update_quote_status(char quote, char c);

#endif