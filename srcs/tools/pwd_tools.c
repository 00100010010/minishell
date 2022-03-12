/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 08:57:21 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/21 18:41:25 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_condition_edge_pwd(t_data *z, char *pwd)
{
	(void)z;
	if (!ft_strcmp("//", pwd))
		return (1);
	if (!ft_strcmp("/", pwd))
		return (1);
	if (!ft_strcmp("//home", pwd))
		return (1);
	if (!ft_strcmp("/home", pwd))
		return (1);
	if (!ft_strcmp(".", pwd))
		return (2);
	if (!ft_strcmp("home", pwd))
		return (3);
	return (0);
}

static void	update_pwd_bckp_utils(t_data *z, char *new_path,
	char *cwd, char *ret)
{
	if (ret)
	{
		free(z->pwd);
		if (is_condition_edge_pwd(z, new_path) == 1)
			z->pwd = ft_strdup(new_path);
		else if (is_condition_edge_pwd(z, new_path) == 3)
			z->pwd = getmyenv(z, "PWD=");
		else
			z->pwd = ft_strdup(cwd);
		free(cwd);
	}
	else
	{
		free(cwd);
		cwd = ft_strdup(z->pwd);
		free(z->pwd);
		z->pwd = ft_strjoin(cwd, "/.");
		free(cwd);
		ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot ac\
cess parent directories: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
}

static void	update_pwd_bckp(t_data *z, char *new_path)
{
	char	*cwd;
	char	*ret;

	if (z->pwd)
	{
		if (z->oldpwd)
			free(z->oldpwd);
		z->oldpwd = ft_strdup(z->pwd);
	}
	cwd = malloc(sizeof(char) * 4096);
	if (!cwd)
		shell_exit(1, "update_pwd_bckp");
	ret = getcwd(cwd, 4096);
	update_pwd_bckp_utils(z, new_path, cwd, ret);
}

int	update_pwd(t_data *z, char *new_path)
{
	update_pwd_bckp(z, new_path);
	if (z->oldpwd_del)
		update_to_env(z, "OLDPWD=", z->oldpwd, 1);
	else if (ft_strlen(z->oldpwd) && !z->oldpwd_del)
		update_to_env(z, "OLDPWD=", z->oldpwd, 2);
	if (z->pwd_del)
		update_to_env(z, "PWD=", z->pwd, 1);
	else
		update_to_env(z, "PWD=", z->pwd, 2);
	return (0);
}
