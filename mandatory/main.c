/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 19:19:39 by hanebaro          #+#    #+#             */
/*   Updated: 2024/06/08 19:19:43 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/pipex.h"

int main(int argc, char **argv)
{
    if(argc != 5)
    {
        write(1, "invalid arguments",17);
        exit(1);
    }
    child_proc(argc,argv);
}
