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
const char *find_path(char *envp[],char *argv)
{
    int i;
    char **p;
    char *r_path;

    i = 0;
    if(ft_strchr(argv,'/'))
        return((const)argv);
    while(envp[i] != NULL)
    {
        if(ft_strncmp(envp[i],"PATH",4) == 0)//verifier est ce que on a PATH or $PATH et le retour de strncmp 
        {
            p = ft_split(envp[i],':');// n oublie pas de identifier que le separateur c :
            i =0;
            while(p[i] != NULL)//verify it s not a bad practice , calculate len table
            {
                r_path = ft_strjoin(p[i],argv);
                if(access(r_path,F_OK) == 1 && access(r_path,R_OK) == 1)//verifier le type de retour de access et est ce que il faut verifier R_OK or not
                    return((const)r_path);
                i++;
            }
            write_err("command not found");
            return(NULL);//i think i need to exit
        }
        i++;
    }
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
    cmd = (char **)malloc(sizeof(char *) * 4);
    if(!cmd)
        return(NULL);
    i = 0;
    while(argv[i] && argv[i] != ' ')
        i++;
    cmd[l++] = my_cpy(i, argv);
    cmd[0] = find_path(envp, cmd[l]);
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
