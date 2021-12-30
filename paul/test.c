#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char        *ft_strcpy(char *dest, char *cpy)
{
    int i;
    int j;
    char    *new;

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
    free (dest);
    return (new);
}

size_t		ft_strlcpy(char *dest, const char *src, size_t dstsize)
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

static char			**ft_malloc_error(char **tab)
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
	unsigned int	i;
	unsigned int	nb_strs;

	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strs++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_strs++;
	return (nb_strs);
}

static void			ft_get_next_str(char **next_str, unsigned int *next_str_len,
					char c)
{
	unsigned int i;

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

char				**ft_split(char const *s, char c)
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

int check(char *str, char c)
{
    int i;
    int nb;

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


int main(int ac, char **av)
{
    int fd;
    int nb;
    int x;
    int y;
    char    *str;
    char    **env;
    int i;

    i = 0; 
    if (ac < 2)
    {
        printf("%s\n", "few arg");
        return (0);
    }
    str = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    x = check(str, ':');
    env = ft_split(str, ':');
    nb = check(av[1], '/');
    i = 0;
    if (nb == 0)
    {
        while (x != -1)
        {
            env[x] = ft_strcpy(env[x], av[1]);
            x--;
        }
    }
    if (nb > 0)
    {
        fd = open(av[1], O_RDONLY);
        if (fd != -1)
            execve(av[1], av, NULL);
        else
            printf("%s\n", "no file found");
    }
    else
    {
        while (i != 9)
        {
            fd = open(env[i], O_RDONLY);
            printf("path : %s | num : %d | fd = %d\n", env[i], i, fd);
            if (fd != -1)
            {
                execve(av[1], av, NULL);
                i = 9;
            }
            else
                i++;
        }
        if (fd == -1)
            printf("%s\n", "no file found");
    }
    return (0);
}