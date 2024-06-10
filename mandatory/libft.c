/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:03:08 by hanebaro          #+#    #+#             */
/*   Updated: 2024/06/09 16:03:11 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		i++;
	}
	return (0);
}
char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] && i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[i - ft_strlen(s1)] && i < ft_strlen(s1) + ft_strlen(s2))
	{
		str[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	str[i] = '\0';
	return (str);
}
char *find_path(char *envp[],char *argv)
{
    int i;
    char **p;
    char *r_path;

    i = 0;
    if(ft_strchr(argv,'/'))
        return(argv);//protect strchr or not
	
    while(envp[i] != NULL)
    {
		// printf("[%s]\n",envp[i]);
        if(ft_strncmp(envp[i],"PATH",4) == 0)//verifier est ce que on a PATH or $PATH et le retour de strncmp 
        {
            p = ft_split(envp[i],':');// n oublie pas de identifier que le separateur c :
            i =0;
            while(p[i] != NULL)//verify it s not a bad practice , calculate len table
            {
				r_path = ft_strjoin(p[i],"/");
                r_path = ft_strjoin(r_path,argv);
                if(access(r_path,F_OK) == 0 && access(r_path,R_OK) == 0)//verifier le type de retour de access et est ce que il faut verifier R_OK or not
                    return(r_path);
                i++;
            }
            
        }
        i++;
    }
	write_err("command not found");
    //write_err("envp PATH not found");
    return(NULL);// i need to exit or not 
}

char *my_cpy(int len, char *argv)
{
    char *str;
    int i;

    str = (char *)malloc(sizeof(char ) * (len + 1));
    if(!str)
        return(NULL);
    i = 0;
    while(argv[i] && i < len)
    {
		str[i] = argv[i];
		i++;
    }
    str[i] = '\0';
    return(str);
}
char **some_var(char *envp[],char *argv)
{
    char **cmd;
    int i;
    int j;
    int l;

    l = 1;
    i = 0;
	cmd = (char **)malloc(sizeof(char *) * 4);
	if (!cmd)
		return (NULL);
    cmd[0] = find_path(envp, cmd[l]);
    while(argv[i] && argv[i] != ' ')
        i++;
    cmd[l++] = my_cpy(i, argv);
    j = 0;
    while(argv[i])
    {
        j++;
        i++;
    }    
    if(j != 0)
        cmd[l++] = my_cpy(j - 1, argv + (i - j + 1));
    else
        cmd[l] = NULL;
    return (cmd);
}














static int	count_words(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*new_word(const char *s, int *i, char c)
{
	int		j;
	int		start;
	int		len;
	char	*words;

	len = ft_strlen(s);
	start = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	words = (char *)malloc ((*i - start) + 1);
	if (words == NULL)
		return (NULL);
	j = 0;
	while (start < *i)
	{
		words[j] = s[start];
		start++;
		j++;
	}
	words[j] = '\0';
	return (words);
}

static char	**free_words(char **words, int j)
{
	while (j >= 0)
	{
		free(words[j]);
		j--;
	}
	free(words);
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	char	**words;

	i = 0;
	if (s == NULL)
		return (NULL);
	words = malloc ((count_words(s, c) + 1) * sizeof (char *));
	if (words == NULL)
		return (NULL);
	j = 0;
	while (j < count_words(s, c) && s[i])
	{
		if (s[i] != c)
		{
			words[j] = new_word(s, &i, c);
			if (words[j] == NULL)
				return (free_words(words, (j - 1)));
			j++;
		}
		i++;
	}
	words[j] = NULL;
	return (words);
}







int	ft_atoi(const char *str)
{
	int		i;
	int		sg;
	long	nb;

	sg = 0;
	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-' )
	{
		if (str[i] == '-')
			sg = 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	if (sg == 1)
		return (nb * -1);
	return (nb);
}