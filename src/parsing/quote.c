/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:54:59 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/30 15:43:00 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	update_quote_status(char quote, char c)
{
	if (quote == '\0' && is_charset(c, "'\""))
		return (c);
	else if (quote != '\0' && quote == c)
		return ('\0');
	else
		return (quote);
}
