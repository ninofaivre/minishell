/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:58:59 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/21 12:55:23 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

void	free_tab_str(char **str_tab)
{
	int	i;

	i = 0;
	if (!str_tab)
		return ;
	while (str_tab[i])
	{
		free(str_tab[i]);
		i++;
	}
	free(str_tab);
}

static int	str_tab_len(char **str_tab)
{
	int	i;

	i = 0;
	if (!str_tab)
		return (0);
	while (str_tab[i])
		i++;
	return (i);
}

char	**add_str_to_str_tab(char **str_tab, char *str)
{
	int		i;
	char	**new_str_tab;

	i = 0;
	new_str_tab = (char **)malloc(sizeof(char *) * (str_tab_len(str_tab) + 2));
	if (!new_str_tab)
	{
		free_tab_str(str_tab);
		return ((char **) NULL);
	}
	while (str_tab && str_tab[i])
	{
		new_str_tab[i] = str_tab[i];
		i++;
	}
	if (str_tab)
		free(str_tab);
	new_str_tab[i] = str;
	new_str_tab[i + 1] = (char *) NULL;
	return (new_str_tab);
}
/*
char	*skip_output_input(char *str)
{
	while (*str)
	{
		str = skip_space(str);
		if (*str == '<' || *str == '>')
		{
			str++;
			if (*str == '<' || *str == '>')
				str++;
			str = skip_space(str);
		}
	}
}
*/
char	*skip_word(char *str)
{
	bool	single_quote;
	bool	double_quote;

	single_quote = false;
	double_quote = false;
	str = skip_space(str);
	update_cote_status(&single_quote, &double_quote, *str);
	while (*str && ((*str != ';' && *str != '|' && *str != ' ' && *str != '>' && *str != '<') || (single_quote == true || double_quote == true)))
	{
		str++;
		update_cote_status(&single_quote, &double_quote, *str);
	}
	return (str);
}

int	word_len(char *str)
{
	bool	single_quote;
	bool	double_quote;
	int		len;

	single_quote = false;
	double_quote = false;
	len = 0;
	if (!str)
		return (0);
	str = skip_space(str);
	update_cote_status(&single_quote, &double_quote, *str);
	while (*str && ((*str != ';' && *str != '|' && *str != ' ' && *str != '>' && *str != '<') || (single_quote == true || double_quote == true)))
	{
		if (!((*str == '\'' && double_quote == false) || (*str == '"' && single_quote == false)))
			len++;
		str++;
		update_cote_status(&single_quote, &double_quote, *str);
	}
	return (len);
}

char	*skip_space(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (str);
}

void	update_cote_status(bool *single_quote, bool *double_quote, char c)
{
	if (c == '"')
	{
		if (*double_quote == true)
			*double_quote = false;
		else if (*single_quote == false)
			*double_quote = true;
	}
	else if (c == '\'')
	{
		if (*single_quote == true)
			*single_quote = false;
		else if (*double_quote == false)
			*single_quote = true;
	}
}