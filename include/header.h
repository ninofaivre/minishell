/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:31:08 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/24 10:18:10 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdbool.h>
# include <unistd.h>

# define PROMPT "NINO BG du 78 $> "

char	*get_command(char *input);

char	*skip_whitespace(char *str);
char	*skip_word(char *str);
bool	comp_one_word(char *str1, char *str2);

#endif