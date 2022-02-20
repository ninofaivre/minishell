/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 15:00:41 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/20 22:49:05 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include <unistd.h>

int	minishell_error(char *call, char *arg, char *error)
{
	write(2, "minishell : ", 12);
	if (call)
	{
		write(2, call, str_len(call));
		write(2, " : ", 3);
	}
	if (arg)
	{
		write(2, "« ", str_len("« "));
		write(2, arg, str_len(arg));
		write(2, " » : ", str_len(" » : "));
	}
	write(2, error, str_len(error));
	write(2, "\n", 1);
	return (0);
}

bool	is_charset(char c, char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (true);
		charset++;
	}
	return (false);
}

int	str_len(char *str)
{
	unsigned int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

int	count_char_in_str(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

int	str_chr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	else
		return (-1);
}
