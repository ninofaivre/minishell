/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 13:50:35 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/24 14:52:08 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	add_int_word(char *word, int status)
{
	int		len;
	char	*str_status;

	i = 0;
	str_status = itoa(status);
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

int	count_redirection(char *str, char guillemet)
{
	int	n_redirection;

	n_redirection = 0;
	while (*str && *str != '|')
	{
		if (is_charset(*str, "><"))
		{
			n_redirection += (*str == guillemet);
			str += (is_charset(*str, "><")) + (is_charset(str[1], "><"));
		}
		str = skip_word(str);
	}
	return (n_redirection);
}
