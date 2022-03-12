/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:07:33 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/24 00:38:40 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_char(int mode, char *name, int pos, int flag)
{
	if (!name || !name[pos])
		return (0);
	if (name[pos] == '+' && flag)
		if ((mode && (name[pos + 1] && name[pos + 1] == '='))
			|| (!mode && (!name[pos + 1])))
			return (1);
	if (ft_isdigit(name[pos]) && !flag)
		return (0);
	if (!ft_isalnum(name[pos]))
		return (0);
	return (1);
}

int	check_flag_plus(t_data *z, char *line)
{
	int	flag_plus;

	(void)z;
	flag_plus = 0;
	if (line[ft_strlen(line) - 1] == '+')
		flag_plus++;
	return (flag_plus);
}

char	**get_arg_split(t_data *z)
{
	char	**arg_split;

	arg_split = split_export(z->builtin->cmd[1]);
	if (arg_split && !arg_split[1])
	{
		write_export(z, ft_strjoin(arg_split[0], "="), 0, 0);
		ft_free_array(arg_split);
		return (NULL);
	}
	else if (!arg_split)
		return (NULL);
	return (arg_split);
}

void	builtin_export_utils(t_data *z, char **arg_split, int flag_plus)
{
	char	*line_title;
	int		i;

	line_title = ft_strjoin(arg_split[0], "=");
	i = ft_array_strncmp(z->env, line_title, ft_strlen(line_title) - 1);
	if (i != -1 && !flag_plus)
		write_export(z, ft_strjoin(line_title, arg_split[1]), i, 2);
	else if (i != -1 && flag_plus)
		write_export(z, ft_strjoin(z->env[i], arg_split[1]), i, 3);
	else if (i == -1)
	{
		if (!ft_strcmp("OLDPWD=", line_title))
			z->oldpwd_del = 0;
		if (!ft_strcmp("PWD=", line_title))
			z->pwd_del = 0;
		write_export(z, ft_strjoin(line_title, arg_split[1]), 0, 4);
	}
	free_and_go_next(z, line_title, arg_split);
}

int	builtin_export(t_data *z)
{
	char	**arg_split;
	int		flag_plus;

	if (!z->builtin->cmd[1])
	{
		ft_put_array(z->export, "\n", 1);
		return (0);
	}
	if (if_invalid_get_next(z))
		return (g_exitg.exit);
	arg_split = get_arg_split(z);
	if (!arg_split)
		return (0);
	flag_plus = check_flag_plus(z, arg_split[0]);
	if (is_valid_name_export(z, arg_split[0], 0) == 2)
		return (0);
	if (flag_plus)
		arg_split[0] = write_export(z, arg_split[0], 0, 1);
	builtin_export_utils(z, arg_split, flag_plus);
	return (0);
}
