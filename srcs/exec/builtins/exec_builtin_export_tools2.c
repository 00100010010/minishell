/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_export_tools3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:07:33 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/22 21:52:05 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_error_message(t_data *z, char *name)
{
	(void)z;
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("' : not a valid identifier", 2);
	g_exitg.exit = 1;
	return (0);
}

int	is_valid_name_export(t_data *z, char *name, int mode)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	g_exitg.exit = 0;
	if (!ft_strcmp(name, "_"))
		return (2);
	while (name[i] && name[i] != '=')
	{
		if (ft_isalpha(name[i]) || name[i] == '_')
			flag++;
		else if (!is_valid_char(mode, name, i, flag))
			return (export_error_message(z, name));
		i++;
	}
	if (name[0] == '=')
		return (export_error_message(z, name));
	return (1);
}

void	*write_export(t_data *z, char *line, int i, int mode)
{
	char	*cpy;

	if (!mode || mode == 4)
		z->env = ft_array_addstr(z->env, line);
	if (mode == 1)
	{
		cpy = ft_substr(line, 0, ft_strlen(line) - 1);
		free(line);
		return (cpy);
	}
	if (mode == 2)
		z->env = ft_array_replace_str_chr(z->env, z->env[i], line);
	if (mode == 3)
	{
		free(z->env[i]);
		z->env[i] = ft_strdup(line);
	}
	free(line);
	return (NULL);
}

int	if_invalid_get_next(t_data *z)
{
	int	ret;

	ret = is_valid_name_export(z, z->builtin->cmd[1], 1);
	if (!ret || !ft_strchr(z->builtin->cmd[1], '='))
	{
		g_exitg.exit = 1;
		if (ret && !ft_strchr(z->builtin->cmd[1], '='))
			g_exitg.exit = 0;
		if (z->builtin->cmd[2])
		{
			z->builtin->cmd = ft_array_delstr(z->builtin->cmd,
					z->builtin->cmd[1]);
			z->cmd->cmd_tab = z->builtin->cmd;
			builtin_export(z);
		}
		return (1);
	}
	return (0);
}

void	free_and_go_next(t_data *z, char *line, char **tab1)
{
	free(line);
	ft_free_array(tab1);
	if (!z->builtin->cmd[2])
		return ;
	z->builtin->cmd = ft_array_delstr(z->builtin->cmd, z->builtin->cmd[1]);
	z->cmd->cmd_tab = z->builtin->cmd;
	builtin_export(z);
	return ;
}
