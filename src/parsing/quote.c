/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 20:54:59 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/21 20:55:35 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_quote	init_quote(void)
{
	t_quote	quote;

	quote.double_quote = false;
	quote.single_quote = false;
	quote.status = false;
	return (quote);
}

void	update_quote_status(t_quote *quote, char c)
{
	if (c == '"')
	{
		if (quote->double_quote == true)
			quote->double_quote = false;
		else if (quote->single_quote == false)
			quote->double_quote = true;
	}
	else if (c == '\'')
	{
		if (quote->single_quote == true)
			quote->single_quote = false;
		else if (quote->double_quote == false)
			quote->single_quote = true;
	}
	if (quote->single_quote == true || quote->double_quote == true)
		quote->status = true;
	else
		quote->status = false;
}
