#include "../includes/pipex_bonus.h"

void	my_exit(void)
{
	perror("Error");
	exit(1);
}

void	error(char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	exit(1);
}