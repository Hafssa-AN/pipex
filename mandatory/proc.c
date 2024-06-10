/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 11:18:04 by hanebaro          #+#    #+#             */
/*   Updated: 2024/06/09 11:18:07 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/pipex.h"

void write_err(char *msg)
{
    perror(msg);
}
int access_file(int i, int argc, char **argv)
{
    
    if(i == 0)
    {
        if(access(argv[1],F_OK) == -1)
        {

            printf("argv = %s\n",argv[1]);
            printf("access = %d\n",access(argv[1],F_OK));
            write_err("No such file or directory");

        }
        if(access(argv[1],R_OK) == -1)
        {
            write_err("permission denied:\n");// a traiter apres
            
            return(0);//chech if is 0 or exit 
        }
        return(1);
    }
    
    else if(i == argc - 4)
    {
        if(access(argv[argc - 4],F_OK) == -1)
            open(argv[argc - 4], O_CREAT);
        return(1);
        
    }
    return(1);
}
void start(int p[], char *argv, int *rd_fp, char **var)
{
    int x;

    x = ft_atoi(argv);
    dup2(x,STDIN_FILENO);
    *rd_fp = dup(p[0]);
    close(p[0]);
    dup2(p[1],STDOUT_FILENO);
    execve(var[0],&var[1],NULL);//je peut ecrire des var env a la pace de null
    close(p[1]);
    exit(0);// exit mn child or not
}
void end(char *argv, int *rd_fp, char **var)
{
    int x;
    
    dup2(*rd_fp,STDIN_FILENO);
    close(*rd_fp);
    x = ft_atoi(argv);
    dup2(x,STDOUT_FILENO);
    execve(var[0],&var[1],NULL);
    //when we dup a file withot open it , we don't need to close it
}
void others(int p[], int *rd_fp, char **var)
{
    dup2(*rd_fp,STDIN_FILENO);
    close(*rd_fp);
    *rd_fp = dup(p[0]);
    close(p[0]);
    dup2(p[1],STDOUT_FILENO);
    execve(var[0],&var[1],NULL);
    close(p[1]);
    //exit or not !!!!!!!!!!!!!!!
}
void child_proc(int argc,char **argv, char *envp[])
{
    int i;
    int p[2];
    int pid;
    int rd_fp;
    char **var;

    i = -1;
    while(++i < argc - 3)
    {
        
        if(i != argc - 4)
            pipe(p);
        pid = fork();
        if(pid == -1)
            write_err("create child process is denied/failed");// exit or not !!
        if(pid == 0)
        {
            printf("[%d]\n",i);
            if((i == 0 || i == argc - 4) && !access_file(i, argc, argv))
                continue;
            
            var =  some_var(envp,argv[i + 2]);printf("heeereee\n");
            if(i == 0)
                start(p, argv[1], &rd_fp, var);
            else if(i == argc - 4)
                end(argv[argc], &rd_fp, var);
            else
            {
                others(p, &rd_fp, var);
                
            }
                
        }
        
    }
}
//char *const argv[]