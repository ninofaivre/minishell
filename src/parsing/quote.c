/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:54:59 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/23 16:16:15 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_quote	init_quote(void)
{
	t_quote	quote;

	quote.double_q = false;
	quote.single_q = false;
	quote.status = false;
	return (quote);
}

void	update_quote_status(t_quote *quote, char c)
{
	if (c == '"')
	{
		if (quote->double_q == true)
			quote->double_q = false;
		else if (quote->single_q == false)
			quote->double_q = true;
	}
	else if (c == '\'')
	{
		if (quote->single_q == true)
			quote->single_q = false;
		else if (quote->double_q == false)
			quote->single_q = true;
	}
	if (quote->single_q == true || quote->double_q == true)
		quote->status = true;
	else
		quote->status = false;
}
