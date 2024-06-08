/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:29:42 by hanebaro          #+#    #+#             */
/*   Updated: 2024/04/20 19:29:46 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"
int	ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == (char)c)
			return (i + 1);
		i++;
	}
	return (0);
}
void cut_path()
{
     
}
void talmnb3d(char *argv[1],char *envp[])
{
    if(ft_strchr(argv[1], '/'))
    {}

}
int main(int argc, char *argv[], char *envp[])
{
    if(argc != 5)
    {
        write(1, "invalid arguments",17);
        exit(1);
    }
    // talmnb3d(*argv[1],**envp);
    //verifier le file
    if(access(argv[1],F_OK) == -1)
        write(1, "No such file or directory",25);
    if(access(argv[1],R_OK) == -1)
    {
        write(1, "permission denied:",25);
        perror();
        //and print file name , use ft_printf
    }
    // chec cmd1
    char  **opt;
    if(!ft_strchr(argv[2], '/'))// i can use while to 1 a argc -1 ou argc - 2
       opt= ft_split(argv[2]," ");//without // un peu de changement dans split ; en cours de split je verifie si / existe ou nn
    //si on a le chemin de la cmd on split puis on chech l access
    char *pt = cherch_path();//optenir le contenu du pah dans envp sans oublier de supprimer la partie PATH = 
    char **path = ft_split(pt,":");
    int i = 0;
    int y = -1;
    char *r_path;
    while(i < ft_tabsize(*opt[1]) && y == -1)
    {
        y =  access(opt[i], F_OK);
        if(y == -1) 
            continue;
        y =  access(opt[i], X_OK);
        if (y == 0)
            r_path = ft_strjoin(opt[i], argv[1]);
    }
    if(y == -1)
        perror("not found"); exit(-1);
    int p[2];
    pipe(p);

    int pid = fork();
    
    
    if (pid == 0) {
        close(p[0]);
        dup2(p[1],STDOUT_FILENO);
        execve(r_path,*opt[1],NULL);//je peut ecrire des var env a la pace de null
        close(p[1]);
        exit(0);
    }
    int status;
    waitpid(pid, &status, 0);
    if(ft_strchr(argv[3], '/'))
    {}
}
/*
/path/bin/sort

/path/usr/sort

/path3/sdfjkl
*/