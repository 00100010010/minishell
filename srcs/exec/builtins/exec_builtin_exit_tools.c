/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_exit_tools.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:07:33 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/19 15:20:56 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_util(t_data *z)
{
	ft_free_array(z->env);
	if (z->export)
		ft_free_array(z->export);
	free(z->cursor);
	if (z->line)
		free(z->line);
	del_hist(z);
	free(z->pwd);
	if (z->oldpwd)
		free(z->oldpwd);
	if (z->cmd)
	{
		z->cmd = lstcmd_first(z->cmd);
		while (z->cmd->next)
			z->cmd = lstcmd_delone(z->cmd, 1);
		free(z->cmd);
	}
	free(z->builtin);
	close(STDERR_FILENO);
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
}

void	ft_atoi_custom_util(unsigned long long res, int sign, int *flag_max)
{
	if ((res > LONG_MAX && sign == 1)
		|| (res > ((ULLONG_MAX / 2) + 1) && sign == -1))
		*flag_max = 2;
	else if (res == LONG_MAX && sign == 1)
		*flag_max = 1;
	else if (res == ((ULLONG_MAX / 2) + 1) && sign == -1)
		*flag_max = -1;
}
