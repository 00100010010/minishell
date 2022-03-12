/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_cd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:07:33 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/21 16:32:23 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_error(t_data *z, int mode)
{
	char	*output;
	char	*cpy;

	if (!mode)
	{
		cpy = ft_strjoin("minishell: cd: ", z->builtin->path);
		output = ft_strjoin(cpy, ": ");
		free(cpy);
		cpy = ft_strjoin(output, strerror(errno));
		free(output);
		output = ft_strjoin(cpy, "\n");
		free(cpy);
		ft_putstr_fd(output, 2);
		free(output);
		free(z->builtin->path);
		return (1);
	}
	ft_putstr_fd("minishell: cd: trop d'arguments\n", 2);
	return (1);
}

int	cd_home(t_data *z)
{
	char	*home;

	home = getmyenv(z, "HOME=");
	if (home && chdir(home) == -1)
	{
		z->builtin->path = home;
		cd_error(z, 0);
		return (1);
	}
	if (!home)
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return (1);
	}
	chdir(home);
	update_pwd(z, home);
	free(home);
	return (0);
}

int	builtin_cd(t_data *z)
{
	z->builtin->path = 0;
	if (z->builtin->cmd[1])
	{
		if (z->builtin->cmd[2])
			return ((cd_error(z, 1)));
		if (!ft_strcmp("", z->builtin->cmd[1]))
		{
			update_pwd(z, z->builtin->path);
			return (0);
		}
		z->builtin->path = ft_strdup(z->builtin->cmd[1]);
	}
	else
		return ((cd_home(z)));
	if (chdir(z->builtin->path) == 0)
		update_pwd(z, z->builtin->path);
	else if (chdir(z->builtin->path) == -1)
		return ((cd_error(z, 0)));
	free(z->builtin->path);
	return (0);
}
