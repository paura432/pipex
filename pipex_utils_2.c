/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:33:06 by marvin            #+#    #+#             */
/*   Updated: 2024/09/17 17:33:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(void)
{
	perror("\033[31mError");
	printf("\e[0m");
	exit(EXIT_FAILURE);
}

void	close_fds(int fd1, int fd2, int *fd)
{
	close(fd[0]);
	close(fd[1]);
	close(fd1);
	close(fd2);
}
