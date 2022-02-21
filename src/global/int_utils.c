/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:58:57 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/21 16:26:59 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

int	int_len(int nbr)
{
	int	len;

	len = 0;
	if (nbr < 0)
	{
		len++;
		nbr = -nbr;
	}
	while (nbr / 10)
	{
		len++;
		nbr /= 10;
	}
	len++;
	return (len);
}

char	*itoa(int nbr)
{
	int		i;
	char	*str;

	i = int_len(nbr);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		nbr = -nbr;
		str[0] = '-';
	}
	str[i--] = '\0';
	while (nbr / 10)
	{
		str[i--] = (nbr % 10) + 48;
		nbr /= 10;
	}
	str[i] = nbr + 48;
	return (str);
}

int	ft_atoi(char *str)
{
	int	nbr;

	nbr = 0;
	if (!str)
		return (0);
	while (*str && ((nbr * 10) + ((int)*str + 48) < INT_MAX))
	{
		nbr = (nbr * 10) + ((int)*str - 48);
		str++;
	}
	return (nbr);
}
