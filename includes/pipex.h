/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:30:06 by hanebaro          #+#    #+#             */
/*   Updated: 2024/04/20 19:30:29 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
#include <fcntl.h>

void child_proc(int argc,char **argv, char *envp[]);
const char find_path(char *envp[],char *argv);
char *my_cpy(int len, char *argv);
char **some_var(char *envp[],char *argv);

#endif