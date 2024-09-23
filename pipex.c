/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 17:00:18 by pramos            #+#    #+#             */
/*   Updated: 2024/09/18 11:01:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(char **cmd, char **envp)
{
	char	*true_path;
	char	*path;

	if (strchr(cmd[0], '/'))
	{
		if (access(cmd[0], X_OK) == 0)
			execve(cmd[0], cmd, envp);
		else
			error();
	}
	else
	{
		path = find_path(envp);
		if (path == NULL)
			error();
		true_path = change_paths(path, *cmd);
		if (!true_path)
			error();
		execve(true_path, cmd, envp);
		free(true_path);
	}
}

void	child_proces(int *fd, int fd1, char **cmd1, char **envp)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1 || dup2(fd1, STDIN_FILENO) == -1)
		error();
	close(fd[1]);
	close(fd1);
	execute_cmd(cmd1, envp);
}

void	parent_proces(int *fd, int fd2, char **cmd2, char **envp)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1 || dup2(fd2, STDOUT_FILENO) == -1)
		error();
	close (fd[0]);
	close(fd2);
	execute_cmd(cmd2, envp);
}

int	pipex(int fd1, int fd2, char **argv, char **envp)
{
	t_pip	pipex;

	pipe(pipex.fd);
	pipex.cmd[0] = ft_split(argv[2], ' ');
	pipex.cmd[1] = ft_split(argv[3], ' ');
	if (!pipex.cmd[0][0] || !pipex.cmd[1][0])
		return (close_fds(fd1, fd2, pipex.fd), error(), 0);
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
	{
		close(fd2);
		child_proces(pipex.fd, fd1, pipex.cmd[0], envp);
	}
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
	{
		close(fd1);
		parent_proces(pipex.fd, fd2, pipex.cmd[1], envp);
	}
	close_fds(fd1, fd2, pipex.fd);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	return (ft_free(pipex.cmd[0]), ft_free(pipex.cmd[1]), 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd1;
	int	fd2;

	if (argc != 5)
		return (write(1, "arguments error\n", 16), 0);
	fd1 = open(argv[1], O_RDONLY, 0777);
	if (fd1 == -1 || access(argv[1], R_OK) < 0)
		error();
	fd2 = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd2 == -1 || access(argv[4], W_OK | R_OK) < 0)
		error();
	pipex(fd1, fd2, argv, envp);
	close(fd1);
	close(fd2);
	return (0);
}
