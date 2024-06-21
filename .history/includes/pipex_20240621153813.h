/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:30:06 by hanebaro          #+#    #+#             */
/*   Updated: 2024/06/21 15:38:13 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

void child_proc(int argc,char **argv, char *envp[]);
char *find_path(char *envp[],char *argv);
char *my_cpy(int len, char *argv);
char **some_var(char *envp[],char *argv);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2,);
void write_err(char *msg);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(const char *s, char c);
int	ft_atoi(const char *str);
char	*ft_strdup(const char *s1);

#endif