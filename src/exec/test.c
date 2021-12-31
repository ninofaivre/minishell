#include "header.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcpy(char *dest, char *cpy)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(dest) + ft_strlen(cpy) + 1));
	while (dest[i])
	{
		new[i] = dest[i];
		i++;
	}
	while (cpy[j])
	{
		new[i + j] = cpy[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
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

static char	**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
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
	if (!(tab = (char **)malloc(sizeof(char *) * (nb_strs + 1))))
		return (NULL);
	i = 0;
	next_str = (char *)s;
	next_str_len = 0;
	while (i < nb_strs)
	{
		ft_get_next_str(&next_str, &next_str_len, c);
		if (!(tab[i] = (char *)malloc(sizeof(char) * (next_str_len + 2))))
			return (ft_malloc_error(tab));
		ft_strlcpy(tab[i], next_str, next_str_len + 1);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	check(char *str, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == c)
			nb ++;
		i++;
	}
	return (nb);
}

void	test_fork(t_list *list, char **env, char *full_path_split)
{
	int		pid;

	pid = fork();
	if (pid == 0)
		execve(full_path_split, list->argv, env);
	waitpid(pid, 0, 0);
}

static char	**ft_path_exec(char **path_split, char *exec)
{
	int		i;
	char	**path_exec;

	i = 0;
	path_exec = (char **)malloc(sizeof(char *) * (str_tab_len(path_split) + 1));
	if (!path_exec)
		return ((char **) NULL);
	while (*path_split)
	{
		path_exec[i] = ft_strcpy(*path_split, exec);
		i++;
		path_split++;
	}
	path_exec[i] = (char *) NULL;
	return (path_exec);
}

int	execution(t_list *list, char **env)
{
	int		fd;
	int		nb;
	char	*str;
	char	**path_split;
	char	**path_exec;
	int		i;
	char	**argv = (char **)malloc(sizeof(char *) * 1);
	argv[0] = (char *) NULL;

	i = 0; 
	str = search_env_var(env, "$PATH");
	path_split = ft_split(str, ':');
	path_exec = (char **) NULL;
	nb = check(list->argv[0], '/');
	i = 0;
	t_list	*ptr_list = list;
	while (list)
	{
		if (nb == 0)
		{
			path_exec = ft_path_exec(path_split, list->argv[0]);
		}
		if (nb > 0)
		{
			fd = open(list->argv[0], O_RDONLY);
			if (fd != -1)
				execve(list->argv[0], list->argv, env);
			else
				printf("%s\n", "no file found");
		}
		else
		{
			while (path_exec[i])
			{
				fd = open(path_exec[i], O_RDONLY);
				printf("path_split : %s | num : %d | fd = %d\n", path_split[i], i, fd);
				if (fd != -1)
				{
					test_fork(list, env, path_exec[i]);
					break ;
				}
				else
					i++;
			}
			i = 0;
			if (fd == -1)
				printf("%s\n", "no file found");
		}
		list = list->next;
		free_tab_str(path_exec);
	}
	list = ptr_list;
	free_tab_str(path_split);
	return (0);
}