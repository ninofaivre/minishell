/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:31:08 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/24 14:29:48 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdbool.h>
# include <unistd.h>
# include <stdio.h>

# define PROMPT "NINO BG du 78 $> "

int		pwd(void);
int		cd(char *arg_input);
void	command_not_found(char *command_input);

char	*get_command(char *input);
char	*get_arg(char *input);

char	*skip_whitespace(char *str);
char	*skip_word(char *str);
bool	comp_one_word(char *str1, char *str2);
int		word_len(char *str);

#endif