/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/24 16:27:58 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdlib.h>

static size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	if (dstsize == 0)
	{
		return (src_len);
	}
	i = 0;
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '/';
	dest[i + 1] = '\0';
	return (src_len);
}

static unsigned int	ft_get_nb_strs(char const *s, char c)
{
	unsigned int	nb_strs;

	if (!s)
		return (0);
	nb_strs = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		if (*s == c)
		{
			nb_strs++;
			while (*s && *s == c)
				s++;
			continue ;
		}
		s++;
	}
	if (s[-1] != c)
		nb_strs++;
	return (nb_strs);
}

static void	ft_get_next_str(char **next_str, unsigned int *next_str_len, char c)
{
	unsigned int	i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == c)
			return ;
		(*next_str_len)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char			**tab;
	char			*next_str;
	unsigned int	next_str_len;
	unsigned int	nb_strs;
	unsigned int	i;

	if (!s)
		return (NULL);
	nb_strs = ft_get_nb_strs(s, c);
	tab = malloc(sizeof(char *) * (nb_strs + 1));
	if (!(tab))
		return (NULL);
	i = -1;
	next_str = (char *)s;
	next_str_len = 0;
	while (++i < nb_strs)
	{
		ft_get_next_str(&next_str, &next_str_len, c);
		tab[i] = malloc(sizeof(char) * (next_str_len + 2));
		if (!(tab[i]))
			return (free_str_tab(&tab));
		ft_strlcpy(tab[i], next_str, next_str_len + 1);
	}
	tab[i] = NULL;
	return (tab);
}
