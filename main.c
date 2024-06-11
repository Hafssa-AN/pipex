#include <stdio.h>
#include <unistd.h>

int main() {
    char *args[] = { "ls", "-al", NULL };
    char *env[] = { NULL };

    execve("/bin/ls", args, env);

    // Cette ligne ne sera jamais atteinte si execve réussit
    perror("execve");
    return 1;
}
