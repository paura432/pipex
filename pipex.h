/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos <pramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 18:37:49 by pramos            #+#    #+#             */
/*   Updated: 2023/10/23 23:28:09 by pramos           ###   ########.fr       */
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

int		main(int argc, char **argv, char **envp);
char	*find_path(char **envp);
int		pipex(int fd1, int fd2, char **argv, char **envp);
void	execute_cmd(char **cmd, char **envp);
void	child_proces(int *fd, int fd1, char **cmd1, char **envp);
void	parent_proces(int *fd, int fd2, char **cmd2, char **envp);
char	**select_path(char **paths, char **envp, int line, int colum);
void	error(void);
char	*change_paths(char *path, char *cmd);

#endif
