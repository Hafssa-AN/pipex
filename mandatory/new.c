/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 23:28:06 by hanebaro          #+#    #+#             */
/*   Updated: 2024/05/18 23:28:09 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
void her_doc()
{
    open();
    ft_get_next_line();
    write();
}
void write_err(char *msg)
{
    perror(msg);
}
int check_file(char *file)
{
    if(access(file,F_OK) == -1)
    {
        write_err("No such file or directory");
        return (0);
    }
    if(access(file,R_OK) == -1)
    {
        write_err("permission denied:");// a traiter apres
        return(0);
    }
    return(1);
}
const char find_path(char *envp[],char *argv)
{
    int i;
    char **p;
    char *r_path;

    i = 0;
    //calculer la taille du tab ou not !!!!!!!!!!!!!!!!!!
    if(ft_strchr(argv,'/'))
        return((const)argv);
    while(envp[i] != NULL)
    {
        if(ft_strncmp(envp[i],"PATH",4) == 0)//verifier est ce que on a PATH or $PATH et le retour de strncmp 
        {
            p = ft_split(envp[i],':');// n oublie pas de identifier que le separateur c :
            i =0;
            while(p[i] != NULL)//verify it s not a bad practice , calculate len table
            {
                r_path = ft_strjoin(p[i],argv);
                if(access(r_path,F_OK) == 1 && access(r_path,R_OK) == 1)//verifier le type de retour de access et est ce que il faut verifier R_OK or not
                    return((const)r_path);
                i++;
            }
            if(p[i] == NULL)
            {
                write_err("command not found");
                return(NULL);
            }
        }

        i++;
    }
}

char *opt_part(char *argv)
{
    int i;

    i = 0;
    while(argv[i] != '\0')
    {
        if(argv[i] == ' ' || )// tab et si c possible les autres espaces
            return(argv[i + 1]);
    }
    return(NULL);
}
int main(int argc, char *argv[], char *envp[])
{
    if(argc != 5)
    {
        write(1, "invalid arguments",17);
        exit(1);
    }
    //create a child process
    int p[2];
    int pid;
    int i;
    int j;
    int rd_fp;
    char *opt;
    char *r_path;
    
    i = 0;
    while(i < argc - 3)
    {
        if(i != argc - 4)
            pipe(p);
        pid = fork();
        if(pid == -1)
            write_err("create child process is denied/failed");
        if (pid == 0)
        {
            if(i == 0)
                j = check_file(argv[1]);
            else if(i == argc - 4)
                j = check_file(argv[argc]);
            if(j == 0)
                continue;
            opt = opt_part(argv[i + 2]);
            r_path = find_path(argv[i + 2]);
            if(i == 0)
            {
                dup2(argv[1],STDIN_FILENO);
                rd_fp = dup(p[0]);
                close(p[0]);
                dup2(p[1],STDOUT_FILENO);
                execve(r_path,opt,NULL);//je peut ecrire des var env a la pace de null
                close(p[1]);
                exit(0);// exit mn child or not
            }
            else if(i == argc - 4)
            {
                dup2(rd_fp,STDIN_FILENO);
                close(rd_fp);
                dup2(argv[argc],STDOUT_FILENO);
                execve();
                //when we dup a file withot open it , we don't need to close it
            }
            else
            {
                dup2(rd_fp,STDIN_FILENO);
                close(rd_fp);
                rd_fp = dup(p[0]);
                close(p[0]);
                dup2(p[1],STDOUT_FILENO);
                execve();
                close(p[1]);
                //exit or not !!!!!!!!!!!!!!!
            }
            i++;
        }
    }
    i = 0;
    while (i++ < argc - 3)
        wait(NULL);  
}
