/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:31:08 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/21 20:54:07 by nfaivre          ###   ########.fr       */
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
	char			**input;
	char			**output;
	char			**argv;
	struct s_list	*next;
}	t_list;

typedef struct s_quote
{
	bool	single_quote;
	bool	double_quote;
	bool	status;
}	t_quote;

char			**get_output_input(char *input, char guillemet);
char			**get_argv(char *input);

t_list			*init_list(char *input);
int				size_list(char *input);

t_list			*build_list(char *input);
t_list			*free_list(t_list *lists);

void			free_tab_str(char **str_tab);
char			**add_str_to_str_tab(char **str_tab, char *str);

char			*skip_word(char *str);
char			*skip_space(char *str);
unsigned int	word_len(char *str);
bool			is_charset(char c, char *charset);
void			update_quote_status(t_quote *quote, char c);
t_quote			init_quote(void);

int				pwd(void);
int				cd(char *arg_input);
void			command_not_found(char *command_input);

#endif