/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pramos <pramos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:13:47 by pramos            #+#    #+#             */
/*   Updated: 2023/11/13 18:22:10 by pramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	if(!*envp)
		error();
	while (ft_strncmp("PATH=", *envp, 5))
		envp++;
	return (*envp + 5);
}

char	*change_paths(char *paths, char *cmd)
{
	char	**tmp_paths;
	char	*tmp;
	char	*path;

	tmp_paths = ft_split(paths, ':');
	while (*tmp_paths)
	{
		tmp = ft_strjoin(*tmp_paths, "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK & R_OK) == 0)
			return (path);
		free(path);
		tmp_paths++;
	}
	return (NULL);
}

void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}
