#include "../includes/pipex.h"

const char *find_path(char *envp[],char *argv)
{
    int i;
    char **p;
    char *r_path;

    i = 0;
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
            write_err("command not found");
            return(NULL);//i think i need to exit
        }
        i++;
    }
    write_err("envp PATH not found");
    return(NULL);
}