// Fonction pour vérifier si argv est un chemin absolu
char *check_absolute_path(char *argv) {
    if (strchr(argv, '/'))
        return argv;
    return NULL;
}

// Fonction pour trouver la variable PATH dans envp
char *get_path_env(char *envp[]) {
    int i;
    char *path_env = NULL;

    for (i = 0; envp[i]; i++) {
        if (strncmp(envp[i], "PATH=", 5) == 0) {
            path_env = envp[i] + 5;
            break;
        }
    }

    return path_env;
}

// Fonction pour trouver le chemin complet d'un exécutable
char *find_executable(char *path_env, char *argv) {
    char **dirs;
    char *full_path;
    int i;

    dirs = ft_split(path_env, ':');
    for (i = 0; dirs[i]; i++) {
        full_path = ft_strjoin(dirs[i], "/");
        full_path = ft_strjoin(full_path, argv);
        if (access(full_path, X_OK) == 0) {
            ft_free_split(dirs);
            return full_path;
        }
        free(full_path);
    }
    ft_free_split(dirs);

    return NULL;
}

// Fonction principale pour trouver le chemin d'un exécutable
char *find_path(char *envp[], char *argv) {
    char *path_env;
    char *full_path;

    full_path = check_absolute_path(argv);
    if (full_path)
        return full_path;

    path_env = get_path_env(envp);
    if (!path_env) {
        write_err("envp PATH not found");
        return NULL;
    }

    full_path = find_executable(path_env, argv);
    if (!full_path)
        write_err("command not found");

    return full_path;
}