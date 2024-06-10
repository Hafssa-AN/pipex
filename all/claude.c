char *find_path(char *envp[], char *argv)
{
    int i;
    char **p;
    char *r_path;

    i = 0;
    if (ft_strchr(argv, '/'))
        return (ft_strdup(argv)); // Utiliser ft_strdup pour dupliquer la chaîne

    while (envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0) // Vérifier si la chaîne commence par "PATH="
        {
            p = ft_split(envp[i] + 5, ':'); // Séparer la chaîne après "PATH=" en utilisant ':'
            i = 0;
            while (p[i] != NULL)
            {
                r_path = ft_strjoin(p[i], "/"); // Ajouter '/' à la fin du chemin
                r_path = ft_strjoin_free(r_path, argv, 1); // Concaténer argv et libérer r_path
                if (access(r_path, X_OK) == 0) // Vérifier si le fichier est exécutable
                {
                    ft_free_split(p); // Libérer le tableau de chaînes p
                    return (r_path);
                }
                free(r_path); // Libérer r_path pour passer à la prochaine itération
                i++;
            }
            ft_free_split(p); // Libérer le tableau de chaînes p
            write_err("command not found");
            return (NULL); // Sortir de la fonction
        }
        i++;
    }
    write_err("envp PATH not found");
    return (NULL); // Sortir de la fonction
}

char *my_cpy(char *argv)
{
    char *str;
    int len;

    len = ft_strlen(argv);
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    ft_strlcpy(str, argv, len + 1); // Utiliser ft_strlcpy pour copier la chaîne de façon sécurisée
    return (str);
}

char **some_var(char *envp[], char *argv)
{
    char *const cmd[4] = {NULL}; // Initialiser le tableau cmd avec NULL
    int i, j, l;

    l = 1;
    i = 0;

    cmd[0] = find_path(envp, argv);
    while (argv[i] && argv[i] != ' ')
        i++;
    cmd[l++] = my_cpy(argv);
    j = i;
    while (argv[j])
        j++;
    if (j != i)
        cmd[l++] = my_cpy(argv + i + 1);
    return ((char **)cmd); // Casting nécessaire pour éviter un avertissement
}