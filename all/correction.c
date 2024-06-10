char *find_path(char *envp[],char *argv)
{
    int i;
    char **p;
    char *r_path;

    i = 0;
    if(ft_strchr(argv,'/'))
        return(argv);
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
                    return(r_path);
                i++;
            }
            write_err("command not found");
            return(NULL);//i think i need to exit
        }
        i++;
    }
    //write_err("envp PATH not found");
    return(NULL);// i need to exit or not 
}

char *my_cpy(int len, char *argv)
{
    char *str;
    int i;

    str = (char *)malloc(sizeof(char ) * (len + 1));
    if(!str)
        return(NULL);
    i = 0;
    while(argv[i] && i < len)
    {
		str[i] = argv[i];
		i++;
    }
    str[i] = '\0';
    return(str);
}
char **some_var(char *envp[],char *argv)
{
    char *cmd[4];
    char const * tab[4];
    int i;
    int j;
    int l;

    l = 1;
    i = 0;

    cmd[0] = find_path(envp, cmd[l]);
    while(argv[i] && argv[i] != ' ')
        i++;
    cmd[l++] = my_cpy(i, argv);
    j = 0;
    while(argv[i])
    {
        j++;
        i++;
    }    
    if(j != 0)
        cmd[l++] = my_cpy(j - 1, argv + (i - j + 1));
    else
        cmd[l] = NULL;
    tab[0] = cmd[0];
    tab[1] = cmd[1];
    tab[2] = cmd[2];
    tab[3] = cmd[3];
    return (tab);
}