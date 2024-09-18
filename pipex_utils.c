/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:13:47 by pramos            #+#    #+#             */
/*   Updated: 2024/09/17 17:33:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	if (!*envp)
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

	if (!paths || !cmd)
		return (NULL);
	tmp_paths = ft_split(paths, ':');
	if (!tmp_paths)
		return (NULL);
	while (*tmp_paths)
	{
		tmp = ft_strjoin(*tmp_paths, "/");
		if (!tmp)
			return (ft_free(tmp_paths), NULL);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK | R_OK) == 0)
			return (path);
		free(path);
		tmp_paths++;
	}
	ft_free(tmp_paths);
	return (NULL);
}

void	ft_free(char **matriz)
{
	int	i;

	i = -1;
	while (matriz[++i])
		free(matriz[i]);
	free(matriz);
}
