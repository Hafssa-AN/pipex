/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 07:29:54 by hanebaro          #+#    #+#             */
/*   Updated: 2024/06/24 15:46:51 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char **exec_var(char **envp, char *argv)
{
    char	**cmd;
    char    *path;
    int i;
    int ex;

    i = 0;
    ex = 0;
    if(!ft_strcmp(argv,"\0"))
        error("command not found:");
    while(argv[i])
    {
        if(argv[i++] != 32)
            ex = 1;
    }
    if(ex == 0)   
        error("permission denied :");
    
    cmd = ft_split(argv, ' ');
    path = find_path(envp, cmd[0]);
    free(cmd[0]);
    cmd[0] = path;
    return (cmd);
}

void	pipes(char *cmd, char **envp, int *input_fd)
{
	int		p[2];
	pid_t	pid;
	char	**var;

	if (pipe(p) == -1)
		my_exit();
	pid = fork();
	if (pid == -1)
		my_exit();
	if (pid == 0)
	{
		close(p[0]);
		if (input_fd)
		{
			dup2(*input_fd, STDIN_FILENO);
			close(*input_fd);
		}
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
		var = exec_var(envp, cmd);
		if (execve(var[0], var, envp) == -1)
			my_exit();
	}
	some_instr(p,)
	close(p[1]);
	if (input_fd)
		close(*input_fd);
	*input_fd = p[0];
}

void	normal(int fd[], char **argv, int argc)
{
	fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] == -1)
		exit(1);
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
		my_exit();
	dup2(fd[0], STDIN_FILENO);
}

void	end(int fd[], char *cmd, char **envp, int input_fd)
{
	pid_t	pid;
	char	**var;

	pid = fork();
	if (pid == -1)
		my_exit();
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(input_fd);
		var = exec_var(envp, cmd);
		if (execve(var[0], var, envp) == -1)
			my_exit();
	}
	close(fd[1]);
	close(input_fd);
	close(fd[0]);
}

int	main(int argc, char **argv, char *envp[])
{
	int	i;
	int	fd[2];
	int	input_fd;

	i = 2;
	if (argc != 5)
		return (write(2, "Invalid number of arguments\n", 28));
	normal(fd, argv, argc);
	input_fd = fd[0];
	while (i < argc - 2)
		pipes(argv[i++], envp, &input_fd);
	end(fd, argv[argc - 2], envp, input_fd);
	while (wait(NULL) > 0)
		;
	close(fd[0]);
	close(fd[1]);
	return (0);
}
