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

char	*concat(char *str1, char *str2)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!new_str)
		return ((char *) NULL);
	while (str1 && *str1)
		new_str[i++] = *str1++;
	while (str2 && *str2)
		new_str[i++] = *str2++;
	new_str[i] = '\0';
	return (new_str);
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



pid_t	test_fork(t_list *list, char **env, char *executable, int *read_pipe, int *write_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (read_pipe)
			close(read_pipe[1]);
		if (write_pipe)
			close(write_pipe[0]);
		if (read_pipe)
			dup2(read_pipe[0], 0);
		if (write_pipe)
			dup2(write_pipe[1], 1);
		execve(executable, list->argv, env);
		_exit(EXIT_FAILURE);
	}
	else
	{
		if (read_pipe)
		{
			close(read_pipe[0]);
			close(read_pipe[1]);
		}
		return (pid);
	}
}

int	builtin(t_list *list, char ***env, int *read_pipe, int *write_pipe)
{
	close(read_pipe[0]);
	close(read_pipe[1]);
	(void)read_pipe;
	(void)write_pipe;
	if (is_same_string(list->argv[0], "export"))
		return(ft_export(list->argv, env));
	else if (is_same_string(list->argv[0], "unset"))
		return(unset(list->argv, env));
	else if (is_same_string(list->argv[0], "cd"))
		return(cd(list->argv));
	else
		return (-1);
}

int	function(t_list *list, char ***env, int *read_pipe, int *write_pipe)
{
	pid_t		pid;
	int			i;
	char		*executable;
	static char	**path;

	pid = 0;
	i = 0;
	if (!path)
		path = ft_split(getenv("PATH"), ':');
	if (!list)
	{
		free(path);
		path = (char **) NULL;
		return (0);
	}
	if (is_same_string(list->argv[0], "cd") || is_same_string(list->argv[0], "export") || is_same_string(list->argv[0], "unset"))
		return(builtin(list, env, read_pipe, write_pipe));
	else if (is_same_string(list->argv[0], "echo") || is_same_string(list->argv[0], "pwd") || is_same_string(list->argv[0], "env"))
		return(test_fork(list, *env, list->argv[0], read_pipe, write_pipe));
	if (count_char_in_str(list->argv[0], '/'))
	{
		if (access(list->argv[0], X_OK) != -1)
			pid = test_fork(list, *env, list->argv[0], read_pipe, write_pipe);
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
				pid = test_fork(list, *env, executable, read_pipe, write_pipe);
				free(executable);
				break ;
			}
			free(executable);
			i++;
		}
		if (!path[i])
			printf("File not found !\n");
	}
	return (pid);
}

int	**init_pipes(t_list *list)
{
	int		n_cmd;
	t_list	*ptr_list;
	int		**pipes;

	n_cmd = 0;
	ptr_list = list;
	while (list)
	{
		list = list->next;
		n_cmd++;
	}
	if (n_cmd == 0)
		return ((int **) NULL);
	pipes = (int **)malloc(sizeof(int *) * n_cmd);
	pipes[--n_cmd] = (int *) NULL;
	while (n_cmd--)
	{
		pipes[n_cmd] = (int *)malloc(sizeof(int) * 2);
		pipe(pipes[n_cmd]);
	}
	list = ptr_list;
	return (pipes);
}

int	wait_function(int pid, int n_cmd)
{
	int status;
	int	child_pid;
	int to_return;

	while (n_cmd--)
	{
		child_pid = wait(&status);
		if (child_pid == pid)
			to_return = WEXITSTATUS(status);
	}
	return (to_return);
}

int	execution(t_list *list, char ***env)
{
	int 	**pipes = init_pipes(list);
	t_list	*ptr_list;
	int		i = -1;
	int		pid;
	int		status;

	ptr_list = list;
	while (list)
	{
		if (i == -1)
			function(list, env, (int *) NULL, pipes[i + 1]);
		else if (!list->next)
			pid = function(list, env, pipes[i], (int *) NULL);
		else
			function(list, env, pipes[i], pipes[i + 1]);
		i++;
		list = list->next;
	}
	status = wait_function(pid, ++i);
	function(list, env, (int *)NULL, (int *)NULL);
	list = ptr_list;
	return (status);
}
