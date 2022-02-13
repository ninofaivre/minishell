/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 18:42:09 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/13 14:57:05 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_ERROR_H
# define MINISHELL_ERROR_H

int	minishell_error(char *call, char *arg, char *error);

# define VOIDPIPE "syntax error near symbol \"|\""
# define VOIDINPUT "syntax error near symbol \"<\""
# define VOIDOUTPUT "syntax error near symbol \">\""
# define CMD "command not found"
# define ALLOC "allocation error (a malloc failed)"
# define MAXARG "too many arguments"
# define NOTDIR "the file you are trying to access is not a directory"
# define INACCESSIBLE "unable to access to the file or directory specified"
# define UNDEFINED "undefined"
# define CREAT "unable to create the file or directory specified"
# define CHARNOTINT "int arg needed"
# define INTTOOHIGH "int arg is too high (see limits.h LLONG_MAX)"
# define MAXFDPROC "too many file descriptors are open by the process (there may be an fd leak or you\
tryed to run too many pipes at one time)"
# define MAXFDSYS "too many file descriptors are open by the system"
# define WRONGENVVAR "env var should contain only underscore, digits and alphabetics char and not\
start by a digit"

#endif