#include "../includes/pipex_bonus.h"

char **exec_var(char **envp, char *argv)
{
    char	**cmd;
    char    *path;

    cmd = ft_split(argv, ' ');
    path = find_path(envp, cmd[0]);
    cmd[0] = path;
    return (cmd);
}

void	pipes(char *cmd, char **envp)
{
    int		p[2];
	pid_t	pid;
    char    **var;

    if (pipe(p) == -1)
		my_exit();
	pid = fork();
	if (pid == -1)
		my_exit();
    if (pid == 0)
    {
        close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
        var = exec_var(envp, cmd);
        printf("Avant l'exécution de la commande : %s\n", cmd);
        exit(1);
        if (execve(var[0], &var[1], envp) == -1)
        {
            perror("execve");
            my_exit();
        }
        printf("Après l'exécution de la commande : %s\n", cmd);
    }
    {
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		close(p[0]);	
	}
}
void    normal(int fd[], char **argv, int argc)
{
    fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd[1] == -1)
		exit(1);
    fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
		my_exit();
	dup2(fd[0], STDIN_FILENO);
}

void	end(int fd[], char *cmd, char **envp)
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
		dup2(fd[1], STDOUT_FILENO);
		var = exec_var(envp, cmd);
		printf("Avant l'exécution de la commande : %s\n", cmd);
        if (execve(var[0], &var[1], envp) == -1)
        {
            perror("execve");
            my_exit();
        }
        printf("Après l'exécution de la commande : %s\n", cmd);
	}
}

int	main(int argc, char **argv, char *envp[])
{
    int i;
    int fd[2];

    i = 2;
    if (argc < 5)
        return (write(2, "Invalid number of arguments\n", 28));
    if (argv[1] && !ft_strcmp("here_doc", argv[1]))
    {
        here_doc(argc, argv, fd);
        i++;
    }     
    else
        normal(fd, argv, argc);
    
    while (i < argc - 2)
    {
        printf("Début de la fonction pipes()\n");
        
        pipes(argv[i++], envp);
    }
        
    printf("Fin de la fonction pipes()\n");
    end(fd, argv[argc - 2], envp);
	while (wait(NULL) > 0)
		;
	close(fd[0]);
    close(fd[1]);
    while(1){};
	return (0);
}
