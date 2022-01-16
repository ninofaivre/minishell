/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:12:09 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/16 12:21:06 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <header.h>

static void	print_str_tab(char **str_tab)
{
	if (!str_tab)
		return ;
	while (*str_tab)
		printf("%s\n", *str_tab++);
}

int	ft_env(char **argv, char **env)
{
	if (str_tab_len(argv) != 1)
	{
		minishell_error("env : too much args\n", (char *) NULL, '\0');
		return (1);
	}
	print_str_tab(env);
	return (0);
}

bool	comp_env_var_name(char *env_var, char *name)
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

char	**search_in_env(char *name, char **env)
{
	int	i;
	int	j;
	
	while (*env)
	{
		i = 0;
		j = 0;
		while ((*env)[i] == name[j] && (*env)[i] && name[j])
		{
			i++;
			j++;
		}
		if (!name[j] && (*env)[i] == '=')
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
	while (*env[j])
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

static char	*str_dupe(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!str)
		return ((char *) NULL);
	new_str = (char *)malloc(sizeof(char) * (str_len(str) + 1));
	if (!new_str)
		return ((char *) NULL);
	while (*str)
		new_str[i++] = *str++;
	new_str[i] = '\0';
	return (new_str);
}

int	unset(char **argv, char ***env)
{
	argv++;
	while (*argv)
		unset_one_var(*argv++, env);
	return (0);
}

int	ft_export(char **argv, char ***env)
{
	char	*str;
	char	**ptr_env_var;

	str = (char *) NULL;
	ptr_env_var = (char **) NULL;
	argv++;
	while (*argv)
	{
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
