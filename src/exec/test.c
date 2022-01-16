#include "header.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*concat(char *dest, char *cpy)
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

int	count_char_in_str(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

bool	is_same_string(char *str1, char *str2)
{
	if ((!str1 && str2) || (str1 && !str2))
		return (false);
	else if (!str1 && !str2)
		return (true);
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (true);
	else
		return (false);
}

void	write_str_tab_to_fd(char **str_tab, int fd)
{
	while (*str_tab)
	{
		write(fd, *str_tab, str_len(*str_tab));
		write(fd, "\n", 1);
		str_tab++;
	}
}

int	doubleinput(char *eof, bool need_pipe)
{
	int		pipe_tab[2];
	char	**str_tab;
	char	*input;

	str_tab = (char **) NULL;
	input = readline(">");
	while (!is_same_string(input, eof))
	{
		str_tab = add_str_to_str_tab(str_tab, input);
		input = readline(">");
	}
	if (need_pipe == false)
	{
		free_tab_str(str_tab);
		free(input);
		return (0);
	}
	else
	{
		pipe(pipe_tab);
		write_str_tab_to_fd(str_tab, pipe_tab[1]);
		close(pipe_tab[1]);
		free_tab_str(str_tab);
		free(input);
		return (pipe_tab[0]);
	}
}

void	take_input(t_redirection *input, int *read_pipe)
{
	int	fd;
	int	i;

	i = 0;
	close(read_pipe[0]);
	while (input[i].content)
	{
		if (input[i].is_double == true)
		{
			fd = doubleinput(input[i].content, !input[i + 1].content);
			if (fd != -1 && !input[i + 1].content)
				dup2(fd, 0);
		}
		else
		{
			if (access(input[i].content, R_OK) == -1)
			{
				printf("Impossible d'accéder au fichier (%s) !\n", input[i].content);
				exit(EXIT_FAILURE);
			}
			else if (!input[i + 1].content)
			{
				fd = open(input[i].content, O_RDONLY);
				dup2(fd, 0);
				break ;
			}
		}
		i++;
	}
}

void	take_output(t_redirection *output, int *write_pipe)
{
	int	fd;
	int	i;

	i = 0;
	close(write_pipe[1]);
	while (output[i].content)
	{
		if (output[i].is_double == true)
			fd = open(output[i].content, O_APPEND | O_RDWR | O_CREAT, 0644);
		else
			fd = open(output[i].content, O_TRUNC | O_RDWR | O_CREAT, 0644);
		if (fd != -1)
		{
			if (!output[i + 1].content)
				dup2(fd, 1);
			else
				close(fd);
		}
		else
		{
			printf("Impossible de créer le fichier !\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	test_fork(t_list *list, char ***env, char *executable, int *read_pipe, int *write_pipe)
{
	pid_t	pid;
	int		status = 0;

	pid = fork();
	if (pid == 0)
	{
		close(read_pipe[1]);
		close(write_pipe[0]);
		if (list->input[0].content)
			take_input(list->input, read_pipe);
		else
			dup2(read_pipe[0], 0);
		if (list->output[0].content)
			take_output(list->output, write_pipe);
		else if (list->next)
			dup2(write_pipe[1], 1);
		else
			close(write_pipe[1]);
		execve(executable, list->argv, *env);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(read_pipe[0]);
		close(read_pipe[1]);
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
}

int	function(t_list *list, char ***env, int *read_pipe, int *write_pipe)
{
	int			status;
	int			i;
	char		*executable;
	static char	**path;

	status = 127;
	i = 0;
	if (!path)
		path = ft_split(getenv("PATH"), ':');
	if (!list)
	{
		free(path);
		path = (char **) NULL;
		return (0);
	}
	if (count_char_in_str(list->argv[0], '/'))
	{
		if (access(list->argv[0], X_OK) != -1)
			status = test_fork(list, env, list->argv[0], read_pipe, write_pipe);
		else
			printf("File not found !\n");
	}
	else
	{
		while (path[i])
		{
			executable = concat(path[i], list->argv[0]);
			if (access(executable, X_OK) != -1)
			{
				status = test_fork(list, env, executable, read_pipe, write_pipe);
				free(executable);
				break ;
			}
			free(executable);
			i++;
		}
		if (!path[i])
			printf("File not found !\n");
	}
	return (status);
}

void	swap_pipe(int *pipe1, int *pipe2)
{
	int	tmp;

	tmp = pipe1[0];
	pipe1[0] = pipe2[0];
	pipe2[0] = tmp;
	tmp = pipe1[1];
	pipe1[1] = pipe2[1];
	pipe2[1] = tmp;
}

int	execution(t_list *list, char ***env)
{
	int		read_pipe[2];
	int		write_pipe[2];
	int		status;
	t_list	*ptr_list;

	pipe(read_pipe);
	pipe(write_pipe);
	status = 0;
	ptr_list = list;
	while (list)
	{
		status = function(list, env, read_pipe, write_pipe);
		pipe(read_pipe);
		swap_pipe(read_pipe, write_pipe);
		list = list->next;
	}
	function(list, env, read_pipe, write_pipe);
	list = ptr_list;
	close(read_pipe[0]);
	close(read_pipe[1]);
	close(write_pipe[0]);
	close(write_pipe[1]);
	return (status);
}
