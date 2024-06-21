/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 07:33:08 by hanebaro          #+#    #+#             */
/*   Updated: 2024/06/21 07:57:17 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PIPEX_BONUS_H
#define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




void my_exit();
void error(char *str);
char	*get_next_line(int fd);
void here_doc(int argc, char **argv);
size_t	ft_strlen(char *s);
int	ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2, int x);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char *find_path(char *envp[], char *argv);
char **some_var(char *envp[],char *argv);
char	**ft_split(const char *s, char c);
//ajouter static or not before fontion name
#endif