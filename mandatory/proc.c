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


int access_file(int i, int argc, char **argv)
{
    int j;

    if(i == 0)
    {
        if(access(argv[1],F_OK) == -1)
            {
                write_err("No such file or directory");
                return (0);
            }
            if(access(argv[1],R_OK) == -1)
            {
                write_err("permission denied:");// a traiter apres
                return(0);
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
char **some_var()
{
    char *r_path;
    char **cmd;

    cmd = cmd_part(argv[i + 2]);
    r_path = find_path(argv[i + 2]);
}
void start(int p[], int i, char **argv, int *rd_fp)
{
    int rd_fp;

    dup2(argv[1],STDIN_FILENO);
    rd_fp = dup(p[0]);
    close(p[0]);
    dup2(p[1],STDOUT_FILENO);
    execve(r_path,cmd,NULL);//je peut ecrire des var env a la pace de null
    close(p[1]);
    exit(0);// exit mn child or not
}



void end(int i, char **argv, int *rd_fp)
{
    
}
void others(int p[], int i, char **argv, int *rd_fp)
{
    
}
void child_proc(int argc,char **argv)
{
    int i;
    int p[2];
    int pid;
    int rd_fp;
    char **var;

    i = 0;
    while(i < argc - 3)
    {
        if(i != argc - 4)
            pipe(p);
        pid = fork();
        if(pid == -1)
            write_err("create child process is denied/failed");// exit or not !!
        if((i == 0 || i == argc - 4) && !access_file(i, argc, argv))
            continue;
        var =  some_var();
        if(i == 0)
            start(p, i, argv, &rd_fp);
        else if(i == argc - 4)
            end(i, argv, &rd_fp);
        else
            rd_fp = others(p, i, argv, &rd_fp);
        i++;
    }
}
