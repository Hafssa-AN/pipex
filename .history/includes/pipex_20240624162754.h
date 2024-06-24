/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:30:06 by hanebaro          #+#    #+#             */
/*   Updated: 2024/06/24 16:27:54 by hanebaro         ###   ########.fr       */
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

void	my_exit(void);
void	error(char *str);
char	*find_path(char *envp[], char *argv);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2, int x);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
intft_strcmp(const char *s1, const char *s2);
char	**ft_split(const char *s, char c);
void	pipes(char *cmd, char **envp, int *input_fd);

#endif