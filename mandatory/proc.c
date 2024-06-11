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
int access_file(int i, char **argv)
{
    
    int fd;
    
    fd = 0;
    if(i == 0)
    {
        if(access(argv[1],F_OK) == -1)
        {
            // printf("access = %d\n",access(argv[1],F_OK));
            write_err("No such file or directory");
            return(0);
        }
        if(access(argv[1],R_OK) == -1)
        {
            write_err("permission denied:\n");// a traiter apres 
            return(0);//chech if is 0 or exit 
        }
    }
    // check r_ok outfile !!!!!!!!!
    return(1);
}
void start(int *p, char *argv, int *rd_fp, char **var)
{
    
    int fd;
    printf("[%s]\n",argv);
    fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd == -1)
    {
        write_err("Error opening input file");
        exit(1); // Sortir du programme en cas d'erreur
    }
    dup2(fd,STDIN_FILENO);
    close(fd);
    *rd_fp = dup(p[0]);
    close(p[0]);
    // printf("p[0] = %d\n",STDIN_FILENO);
    // printf("p[1] = %d\n",p[1]);
    
    dup2(STDOUT_FILENO,p[1]);
    // printf("before p[1] = %s\n",var[3]);exit(1);
    execve(var[0],&var[1],NULL);//je peut ecrire des var env a la pace de null
    // Si execve réussit, le processus enfant est remplacé par la commande exécutée
    // Sinon, le code suivant sera exécuté (en cas d'erreur)
    
    write_err("Error executing command");
    exit(1);// exit mn child or not
}
void end(char *argv, int *rd_fp, char **var)
{

    int fd;

    fd = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        write_err("Error opening input file");
        exit(1); // Sortir du programme en cas d'erreur
    }
    dup2(*rd_fp,STDIN_FILENO);
    close(*rd_fp);
    dup2(fd,STDOUT_FILENO);
    close(fd);
    execve(var[0],&var[1],NULL);
    //when we dup a file without open it , we don't need to close it
    write_err("Error executing command");
    exit(1);
}
void others(int p[], int *rd_fp, char **var)
{
    dup2(*rd_fp,STDIN_FILENO);
    close(*rd_fp);
    *rd_fp = dup(p[0]);
    close(p[0]);
    dup2(p[1],STDOUT_FILENO);
    close(p[1]);
    execve(var[0],&var[1],NULL);
    write_err("Error executing command");
    exit(1);
    //exit or not !!!!!!!!!!!!!!!
}
void child_proc(int argc,char **argv, char *envp[])
{
    // (void)argv;
    // (void)envp;
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
            // printf("heeereee\n");
            // printf("[%d]\n",i);
            // printf("hiiii");
            // exit(1);
            // printf("before start and argc - 4 = %d\n",argc-4);
            // printf("bin if [%d]]\n",access_file(i, argv));
            
            if(i == 0  && !access_file(i, argv))
            {
                continue;    
            }  
            var =  some_var(envp,argv[i + 2]);
            if(i == 0)
            {
                printf("in start\n");
                start(p, argv[1], &rd_fp, var);
            }
                
            else if(i == argc - 4)
            {
                printf("in end\n");
                end(argv[argc], &rd_fp, var);
            }
                
            else
            {
                printf("in others\n");
                others(p, &rd_fp, var);
                
            }
            
        }   
        if(i == 0)
            break; 
    }   
        
    
}
//char *const argv[]