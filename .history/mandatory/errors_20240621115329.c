/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanebaro <hanebaro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 07:43:31 by hanebaro          #+#    #+#             */
/*   Updated: 2024/06/21 11:53:29 by hanebaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	my_exit(void)
{
	perror("Error");
	exit(1);
}

void	error(char *str)
{
	if(str)
		write(2,str,ft_strlen(str));
	exit(1);
}