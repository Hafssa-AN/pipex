#include <stdio.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
    int fd;
    fd = open(argv[argc - 1], O_RDONLY);
	    if (fd == -1)
        {
            printf("in in %s\n",argv[1]);
            exit(1);
            my_exit();
        }
}