/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:14:32 by hanebaro          #+#    #+#             */
/*   Updated: 2024/06/21 12:06:24 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char    *my_cpy(int len, char *argv)
{
	char    *str;
	int     i;

	str = (char *)malloc(sizeof(char ) * (len + 1));
	if (!str)
		return(NULL);
	i = 0;
	while (argv[i] && i < len)
	{
		str[i] = argv[i];
		i++;
	}
	str[i] = '\0';
	return(str);
}
char	**some_var(char *envp[],char *argv)
{
	char	**cmd;
	int		i;
	int		j;
	int		l;

	l = 1;
	i = 0;
	cmd = (char **)malloc(sizeof(char *) * 4);
	if (!cmd)
		return (NULL);
	while (argv[i] && argv[i] != ' ')
		i++;
	cmd[l++] = my_cpy(i, argv);
	cmd[0] = find_path(envp, cmd[l - 1]);
	cmd[l - 1] = find_path(envp, cmd[l - 1]);
	j = 0;
	while (argv[i])
	{
		j++;
		i++;
	}   
	if (j != 0)
	{
		cmd[l++] = my_cpy(j - 1, argv + (i - j + 1));
	}
	else
		cmd[l] = NULL;
	return (cmd);
}
