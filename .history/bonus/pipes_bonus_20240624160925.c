/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:01:49 by hanebaro          #+#    #+#             */
/*   Updated: 2024/06/24 16:09:25 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	some_instr(int p[], int *input_fd)
{
	close(p[1]);
	if (input_fd)
		close(*input_fd);
	*input_fd = p[0];
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
	some_instr(p, input_fd);
}