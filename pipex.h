/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:37:49 by pramos            #+#    #+#             */
/*   Updated: 2024/09/17 19:02:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "Libft/libft.h"

typedef struct p_pip
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	char	**cmd[2];
}	t_pip;

int		main(int argc, char **argv, char **envp);
char	*find_path(char **envp);
int		pipex(int fd1, int fd2, char **argv, char **envp);
void	execute_cmd(char **cmd, char **envp);
void	child_proces(int *fd, int fd1, char **cmd1, char **envp);
void	parent_proces(int *fd, int fd2, char **cmd2, char **envp);
char	**select_path(char **paths, char **envp, int line, int colum);
void	error(void);
char	*change_paths(char *path, char *cmd);
void	ft_free(char **matriz);
void	close_fds(int fd1, int fd2, int *fd);
void	execute_cmds(char **cmd1, char **cmd2, char **argv);

#endif
