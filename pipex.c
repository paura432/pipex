/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos <pramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:00:18 by pramos            #+#    #+#             */
/*   Updated: 2023/11/13 18:22:43 by pramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(char **cmd, char **envp)
{
	char	*true_path;
	char	*path;

	if ((cmd[0][0] == '.' && cmd[0][1] == '/') || cmd[0][0] == '/')
	{
		if (access(cmd[0], X_OK) == 0)
			execve(cmd[0], cmd, envp);
		else
			error();
	}
	else
	{
		path = find_path(envp);
		true_path = change_paths(path, *cmd);
		if (!true_path)
			error();
		execve(true_path, cmd, envp);
	}
}

void	child_proces(int *fd, int fd1, char **cmd1, char **envp)
{
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
	dup2(fd1, 0);
	close(fd1);
	execute_cmd(cmd1, envp);
}

void	parent_proces(int *fd, int fd2, char **cmd2, char **envp)
{
	close(fd[1]);
	dup2(fd[0], 0);
	close (fd[0]);
	dup2(fd2, 1);
	close(fd2);
	execute_cmd(cmd2, envp);
}

int	pipex(int fd1, int fd2, char **argv, char **envp)
{
	pid_t	pid;
	int		fd[2];
	char	**cmd1;
	char	**cmd2;

	pipe(fd);
	cmd1 = ft_split(argv[2], ' ');
	cmd2 = ft_split(argv[3], ' ');
	pid = fork();
	if (!pid)
		child_proces(fd, fd1, cmd1, envp);
	else
		parent_proces(fd, fd2, cmd2, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	exit (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	int	fd2;

	if (argc != 5)
		error();
	fd1 = open(argv[1], O_RDONLY, 0777);
	if (access(argv[1], R_OK) < 0)
		error();
	if (fd1 == -1)
		error();
	fd2 = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (access(argv[4], W_OK | R_OK) < 0)
		error();
	if (fd2 == -1)
		error();
	pipex(fd1, fd2, argv, envp);
	return (0);
}
