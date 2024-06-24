/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:06:04 by hanebaro          #+#    #+#             */
/*   Updated: 2024/06/24 16:06:05 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	here_doc_input(int *p, char *lim)
{
	char	*line;

	lim = ft_strjoin(lim, "\n", 0);
	close(p[0]);
	dup2(p[1], STDOUT_FILENO);
	close(p[1]);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!ft_strcmp(line, lim) || !line)
		{
			free(line);
            free(lim);
			exit(1);
		}	
		write(1, line, ft_strlen(line));
		free(line);
	}
    free(lim);
}

void	here_doc(int argc, char **argv,int fd[])
{
	pid_t	pid;
	int		p[2];

	if (argc < 6)
		error("add more arguments to 6\n");
    fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd[1] == -1)
		exit(1);
	if (pipe(p) == -1)
		my_exit();
	pid = fork();
	if (pid == -1)
		my_exit();
	if (pid == 0)
		here_doc_input(p, argv[2]);
	else
	{
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		close(p[0]);
		waitpid(pid, NULL, 0);
	}
}
