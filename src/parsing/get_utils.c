/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 13:50:35 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/31 13:51:46 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	add_env_var_to_word(char *word, char *env_var)
{
	unsigned int	env_var_len;

	env_var_len = str_len(env_var);
	while (env_var && *env_var)
		*word++ = *env_var++;
	return (env_var_len);
}

int	count_redirection(char *str, char guillemet)
{
	int	n_redirection;

	n_redirection = 0;
	while (*str && *str != '|')
	{
		if (is_charset(*str, "><"))
		{
			n_redirection += (*str == guillemet) + (str[1] == guillemet);
			str += (is_charset(*str, "><")) + (is_charset(str[1], "><"));
		}
		str = skip_word(str);
	}
	return (n_redirection);
}
