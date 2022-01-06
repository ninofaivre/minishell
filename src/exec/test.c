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

void	test_fork(t_list *list, char **env, char *full_path_split, int *pipe_a, int *pipe_b, int id)
{
	pid_t	pid;
	int		status = 0;

	pid = fork();
	if (pid == 0)
	{
		close(pipe_a[1]);
		close(pipe_b[0]);
		if (id != 0)
			dup2(pipe_a[0], 0);
		else
			close(pipe_a[0]);
		if (list->next)
			dup2(pipe_b[1], 1);
		else
			close(pipe_b[1]);
		execve(full_path_split, list->argv, env);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipe_a[0]);
		close(pipe_a[1]);
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
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
	int		nb;
	char	*str;
	char	**path_split;
	char	**path_exec;
	int		i;

	i = 0; 
	str = search_env_var(env, "$PATH");
	path_split = ft_split(str, ':');
	path_exec = (char **) NULL;
	nb = check(list->argv[0], '/');
	i = 0;
	t_list	*ptr_list = list;
	int	pipe_a[2];
	int	pipe_b[2];
	pipe(pipe_a);
	pipe(pipe_b);
	int	id = 0;
	while (list)
	{
		if (nb == 0)
		{
			path_exec = ft_path_exec(path_split, list->argv[0]);
		}
		if (nb > 0)
		{
			if (access(list->argv[0], X_OK) != -1)
			{
				if (id % 2)
				{
					test_fork(list, env, list->argv[0], pipe_b, pipe_a, id);
					pipe(pipe_b);
				}
				else
				{
					test_fork(list, env, list->argv[0], pipe_a, pipe_b, id);
					pipe(pipe_a);
				}
			}
			else
				printf("%s\n", "no file found");
		}
		else
		{
			while (path_exec[i])
			{
				if (access(path_exec[i], X_OK) != -1)
				{
					if (id % 2)
					{
						test_fork(list, env, path_exec[i], pipe_b, pipe_a, id);
						pipe(pipe_b);
					}
					else
					{
						test_fork(list, env, path_exec[i], pipe_a, pipe_b, id);
						pipe(pipe_a);
					}
					break ;
				}
				else
					i++;
			}
			if (!path_exec[i])
				printf("%s\n", "no file found");
			i = 0;
		}
		list = list->next;
		free_tab_str(path_exec);
		id++;
	}
	list = ptr_list;
	free_tab_str(path_split);
	close(pipe_a[0]);
	close(pipe_a[1]);
	close(pipe_b[0]);
	close(pipe_b[1]);
	return (0);
}