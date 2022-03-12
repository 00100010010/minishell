/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_unset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:07:33 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/19 13:47:14 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_name_unset(char *name)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	if (!ft_strcmp(name, "_"))
		return (2);
	while (name[i])
	{
		if (ft_isalpha(name[i]) || name[i] == '_')
			flag++;
		else if (ft_isspace(name[i]) || (ft_isdigit(name[i]) && !flag)
			|| (!ft_isalnum(name[i]) && name[i] != '_'))
		{
			ft_putstr_fd("minishell: '", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	edge_case_unset(t_data *z, char *value_name)
{
	if (!ft_strcmp("PWD=", value_name))
	{
		if (!z->pwdbckp || !ft_strlen(z->pwdbckp))
		{
			if (z->pwdbckp)
				free(z->pwdbckp);
			z->pwdbckp = ft_strdup(z->pwd);
		}
		free(z->pwd);
		z->pwd = ft_strdup("");
		z->pwd_del = 1;
	}
	if (!ft_strcmp("OLDPWD=", value_name))
	{
		z->oldpwd_del = 1;
		free(z->oldpwd);
		z->oldpwd = ft_strdup("");
	}
}

int	builtin_unset(t_data *z)
{
	int		i;
	char	*value_name;

	if (!z->builtin->cmd[1])
		return (0);
	value_name = ft_strjoin(z->builtin->cmd[1], "=");
	i = ft_array_strncmp(z->env, value_name, ft_strlen(value_name) - 1);
	if (is_valid_name_unset(z->builtin->cmd[1]) && i != -1)
		z->env = ft_array_delstr(z->env, z->env[i]);
	if (!ft_strcmp("PWD=", value_name) || !ft_strcmp("OLDPWD=", value_name))
		edge_case_unset(z, value_name);
	free(value_name);
	if (z->builtin->cmd[2])
	{
		z->builtin->cmd = ft_array_delstr(z->builtin->cmd, z->builtin->cmd[1]);
		z->cmd->cmd_tab = z->builtin->cmd;
		builtin_unset(z);
	}
	return (0);
}
