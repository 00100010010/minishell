/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:07:33 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/21 18:34:45 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*echo_putstr(t_data *z, int i)
{
	if (!i)
		i++;
	while (z->builtin->cmd[i])
	{
		ft_putstr_fd(z->builtin->cmd[i], 1);
		if (z->builtin->cmd[++i])
			ft_putstr_fd(" ", 1);
	}
	return (0);
}

int	parse_n_flag(t_data *z, int i, int k, int count)
{
	count = 0;
	i = 1;
	while (z->builtin->cmd[i])
	{
		k = 0;
		if (z->builtin->cmd[i][k] == '-')
		{
			k++;
			if (!z->builtin->cmd[i][k] || z->builtin->cmd[i][k] != 'n')
				break ;
			while (z->builtin->cmd[i][k] && z->builtin->cmd[i][k] == 'n')
				k++;
			if (z->builtin->cmd[i][k])
				break ;
			i++;
			count++;
		}
		else
			break ;
	}
	if (count)
		return (count + 1);
	return (0);
}

int	builtin_echo(t_data *z)
{
	int	n_flag;
	int	k;
	int	i;
	int	count;

	i = 0;
	k = 0;
	count = 0;
	n_flag = parse_n_flag(z, i, k, count);
	if (!z->builtin->cmd[1])
		echo_putstr(z, n_flag);
	else if ((z->builtin->cmd[1] && !n_flag)
		|| (z->builtin->cmd[2] && n_flag))
		echo_putstr(z, n_flag);
	if (!n_flag)
	{
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
