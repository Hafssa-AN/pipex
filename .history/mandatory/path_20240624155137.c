/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:15:02 by hanebaro          #+#    #+#             */
/*   Updated: 2024/06/24 15:51:37 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	*check_absolute_path(char *argv)
{
	if (ft_strchr(argv, '/'))
		return (argv);
	return (NULL);
}

char	*get_path_env(char *envp[])
{
	int		i;
	char	*path_env;

	i = 0;
	path_env = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (path_env);
}

char	*find_executable(char *path_env, char *argv)
{
	char	**dirs;
	char	*full_path;
	int		i;

	i = 0;
	dirs = ft_split(path_env, ':');
	while (dirs[i])
	{
		full_path = ft_strjoin(dirs[i], "/", 0);
		full_path = ft_strjoin(full_path, argv, 1);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}

char	*find_path(char *envp[], char *argv)
{
	char	*path_env;
	char	*full_path;

	full_path = check_absolute_path(argv);
	if (full_path)
		return (full_path);
	path_env = get_path_env(envp);
	if (!path_env)
	{
		error("envp PATH not found\n");
		return (NULL);
	}
	full_path = find_executable(path_env, argv);
	if (!full_path)
		error("command not found");
	return (full_path);
}
