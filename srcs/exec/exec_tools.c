/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 20:41:54 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/24 00:30:25 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_bin(char *path, char *cmd)
{
	DIR				*dir;
	struct dirent	*dirent;

	dir = opendir(path);
	if (dir)
	{
		dirent = readdir(dir);
		while (dirent)
		{
			if (!ft_strcmp(dirent->d_name, cmd))
			{
				if (dir)
					closedir(dir);
				return (ft_strjoin(path, cmd));
			}
			dirent = readdir(dir);
		}
	}
	if (dir)
		closedir(dir);
	return (NULL);
}

char	*null_if_dir(t_data *z, char *cmd_line)
{
	DIR		*dir;

	(void)z;
	dir = opendir(cmd_line);
	if (dir)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd_line, 2);
		ft_putstr_fd(" : est un dossier\n", 2);
		free(dir);
		g_exitg.exit = 126;
		return (NULL);
	}
	return (ft_strdup(cmd_line));
}

char	**getmypath(t_data *z)
{
	char	**ret;
	char	*path;

	path = NULL;
	path = getmyenv(z, "PATH=");
	if (!path)
		return (NULL);
	ret = ft_split(path, ':');
	free(path);
	return (ret);
}

char	*get_absolute_path(t_data *z, char *cmd_line)
{
	char	**path_splited;
	int		i;
	char	*bin;
	char	*bin_cpy;

	if (!cmd_line)
		return (NULL);
	if (ft_strchr(cmd_line, '/'))
		return ((null_if_dir(z, cmd_line)));
	path_splited = getmypath(z);
	if (!path_splited)
		return (NULL);
	bin = NULL;
	i = 0;
	while (path_splited[i])
	{
		bin_cpy = ft_strjoin(path_splited[i], "/");
		bin = check_bin(bin_cpy, cmd_line);
		free(bin_cpy);
		if (bin)
			break ;
		i++;
	}
	ft_free_array(path_splited);
	return (bin);
}

int	is_built_in(t_cmd *cmd)
{
	const char	*built_in[BUILTINS_COUNT + 2];
	int			i;

	if (cmd->auto_dest)
		return (0);
	built_in[0] = NULL;
	built_in[1] = CMD_PWD;
	built_in[2] = CMD_CD;
	built_in[3] = CMD_ECHO;
	built_in[4] = CMD_EXIT;
	built_in[5] = CMD_ENV;
	built_in[6] = CMD_EXPORT;
	built_in[7] = CMD_UNSET;
	built_in[8] = NULL;
	i = 1;
	cmd->token = lst_token_first(cmd->token);
	while (built_in[i])
	{
		if (!ft_strcmp(built_in[i], cmd->token->word))
			return (i);
		i++;
	}
	return (0);
}
