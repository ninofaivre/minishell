/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:12:09 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/25 17:31:29 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"
#include "global.h"
#include <stdlib.h>

int	builtin_env(char **argv, char **env)
{
	if (str_tab_len(argv) != 1)
	{
		minishell_error("env", MAXARG);
		return (1);
	}
	print_str_tab(env);
	return (0);
}

static bool	comp_env_var_name(char *env_var, char *name)
{
	while (*env_var && *name && *env_var == *name)
	{
		env_var++;
		name++;
	}
	if (*env_var == '=' && !*name)
		return (true);
	else
		return (false);
}

static char	**search_in_env(char *name, char **env)
{
	int	i;

	while (*env)
	{
		i = 0;
		while ((*env)[i] == name[i] && (*env)[i] && name[i] && name[i] != '=')
			i++;
		if ((!name[i] || name[i] == '=') && (*env)[i] == '=')
			return (&(*env));
		env++;
	}
	return ((char **) NULL);
}

static void	unset_one_var(char *name, char ***env)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = (char **) NULL;
	if (!search_in_env(name, *env))
		return ;
	new_env = (char **)malloc(sizeof(char *) * str_tab_len(*env));
	while ((*env)[j])
	{
		if (comp_env_var_name((*env)[j], name))
			free((*env)[j]);
		else
			new_env[i++] = (*env)[j];
		j++;
	}
	new_env[i] = (char *) NULL;
	free(*env);
	*env = new_env;
}

int	builtin_unset(char **argv, char ***env)
{
	argv++;
	while (*argv)
		unset_one_var(*argv++, env);
	return (0);
}

int	builtin_export(char **argv, char ***env)
{
	char	*str;
	char	**ptr_env_var;

	str = (char *) NULL;
	ptr_env_var = (char **) NULL;
	argv++;
	while (*argv)
	{
		if (!(count_char_in_str(*argv, '=')))
		{
			argv++;
			continue ;
		}
		if ((ptr_env_var = search_in_env(*argv, *env)))
		{
			free(*ptr_env_var);
			*ptr_env_var = str_dupe(*argv);
		}
		else
		{
			str = str_dupe(*argv);
			*env = add_str_to_str_tab(*env, str);
		}
		argv++;
	}
	return (0);
}
