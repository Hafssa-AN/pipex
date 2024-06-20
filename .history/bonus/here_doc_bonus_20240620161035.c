#include "../includes/pipex_bonus.h"

void here_doc_input(int *p, char *lim)
{
    char *line;

    while(1)
    {
        dup2(p[1], STDOUT_FILENO);
        close(p[0]);
        line = get_next_line(STDIN_FILENO);
        if(ft_strcmp(line, lim) || !line)// !line not oblig ??!!
            exit(1);
        write(1, line, ft_strlen(line));
    }
}
void here_doc(int argc, char **argv)
{
    pid_t pid;
    int p[2];

    if(argc < 6)
        error("add more arguments");//check apres
    if(pipe(p) == -1)
        my_exit();
    pid = fork();
    if(pid == -1)
        my_exit();
    if(pid == 0)
        here_doc_input(p, argv[2]);
    else
    {
        close(p[1]);
        dup2(p[0],STDIN_FILENO);
        close(p[0]);
        waitpid(pid, NULL, 0);
    }
}