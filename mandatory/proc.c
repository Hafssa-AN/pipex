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

int start()
{

}
int end()
{

}
int others()
{

}
void child_proc(int argc,char **argv)
{
    int i;
    int p[2];
    int pid;
    char *r_path;
    char *cmd;
    int rd_fp;

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
        if(i == 0)
            rd_fp = start();
        else if(i == argc - 4)
            rd_fp = end();
        else
            rd_fp = others();   
    }
}
