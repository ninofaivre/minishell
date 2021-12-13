/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:31:08 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/13 11:20:16 by nfaivre          ###   ########.fr       */
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

typedef struct s_lists
{
	struct s_list	*list;
	struct s_lists	*next;
}	t_lists;

typedef struct s_list
{
	char			*input;
	char			*output;
	char			*command;
	char			*arg;
	struct s_list	*next;
}	t_list;

t_lists	*build_lists(char *input);
t_lists	*free_lists(t_lists *lists);

int		pwd(void);
int		cd(char *arg_input);
void	command_not_found(char *command_input);

bool	comp_one_word(char *str1, char *str2);
int		word_len(char *str);

#endif