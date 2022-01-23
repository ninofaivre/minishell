/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:42:09 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/23 19:28:31 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERROR_H
# define MINISHELL_ERROR_H

int	minishell_error(char *call, char *error);

# define VOIDPIPE "syntax error near symbol \"|\""
# define VOIDINPUT "syntax error near symbol \"<\""
# define VOIDOUTPUT "syntax error near symbol \">\""
# define ALLOC "allocation error (a malloc failed)"
# define MAXARG "too many arguments"

#endif