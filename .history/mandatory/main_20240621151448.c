/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 07:29:54 by hanebaro          #+#    #+#             */
/*   Updated: 2024/06/21 15:14:48 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	pipes(char *cmd, char **envp)
{
	int		p[2];
	pid_t	pid;
	char	**var;
	int		i;

	i = 0;
	if (pipe(p) == -1)
		my_exit();
	pid = fork();
	if (pid == -1)
		my_exit();
	if (pid == 0)
	{
		dup2(p[1], STDOUT_FILENO);
		close(p[0]);
		var = some_var(envp, cmd, i);
		if (execve(var[0], &var[1], envp) == -1)
			my_exit();
	}
	else
	{
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		close(p[1]);
	}
}

void	end(int fd, char *cmd, char **envp)
{
	int		pid;
	char	**var;
	int		i;

	i = 0;
	pid = fork();
	if (pid == -1)
		my_exit();
	if (pid == 0)
	{
		dup2(fd, STDOUT_FILENO);
		var = some_var(envp, cmd, i);
		if (execve(var[0], &var[1], envp) == -1)
			my_exit();
	}
}

void	setup_and_process(int fd, int argc, char **argv, char *envp[])
{
    int	i;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		my_exit();
	dup2(fd, STDIN_FILENO);
    i = 2;
    while (i < argc - 2)
        pipes(argv[i++], envp);
    if (i == argc - 2)
    {
        fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            printf("in argc - 1\n");
            exit(1);
        }
    }
    end(fd, argv[argc - 2], envp);
}

int	main(int argc, char **argv, char *envp[])
{
	int	fd;
	
	fd = 0;
    if (argc != 5)
        return (write(2, "Invalid number of arguments\n", 28));
    
    setup_and_process(fd, argc, argv, envp);
    
    while (wait(NULL) > 0);
    close(fd);
    return (0);
}
