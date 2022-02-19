/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 13:50:35 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/19 20:26:57 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

int	add_int_word(char *word, int status)
{
	int		len;
	char	*str_status;

	str_status = itoa(status);
	if (!str_status)
	{
		minishell_error("parsing ($?)", NULL, ALLOC);
		return (0);
	}
	len = add_str_word(word, str_status);
	free(str_status);
	return (len);
}

int	add_str_word(char *word, char *str)
{
	unsigned int	len;

	len = str_len(str);
	while (str && *str)
		*word++ = *str++;
	return (len);
}

int	count_redirection(char *str)
{
	int	n_redirection;

	n_redirection = 0;
	while (*str && *str != '|')
	{
		if (is_charset(*str, "><"))
		{
			n_redirection++;
			str += (is_charset(*str, "><")) + (is_charset(str[1], "><"));
		}
		str = skip_word(str);
	}
	return (n_redirection);
}
