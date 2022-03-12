/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:25:04 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/22 21:52:40 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_exec_fds(t_data *z, t_cmd *command)
{
	if ((command->prev_sep_type < 2 && command->sep_type == PIPE)
		|| (command->prev_sep_type == PIPE && command->sep_type == PIPE)
		|| (command->filename_out || command->filename_in))
		close_fds(z, 1);
	else if (command->prev_sep_type == PIPE
		&& (command->sep_type < 2 || command->next_sep_type == END))
		close_fds(z, 0);
}

void	free_builtin(t_data *z)
{
	ft_free_array(z->env);
	ft_free_array(z->export);
	free(z->cursor);
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

int	exec_built_in(t_data *z, t_cmd *command)
{
	int	i;

	if (command->auto_dest)
		return (0);
	z->cmd = command;
	command->cmd_tab = conv_cmd_to_tab(command);
	z->builtin->cmd = command->cmd_tab;
	i = is_built_in(command);
	make_redir(z, command);
	if (i == 1)
		g_exitg.exit = builtin_pwd(z);
	else if (i == 2)
		g_exitg.exit = builtin_cd(z);
	else if (i == 3)
		g_exitg.exit = builtin_echo(z);
	else if (i == 4)
		g_exitg.exit = builtin_exit(z);
	else if (i == 5)
		g_exitg.exit = builtin_env(z);
	else if (i == 6)
		g_exitg.exit = builtin_export(z);
	else if (i == 7)
		g_exitg.exit = builtin_unset(z);
	return (g_exitg.exit);
}

int	exec_built_out(t_data *z, t_cmd *command)
{
	if (command->auto_dest)
		return (0);
	command->cmd_tab = conv_cmd_to_tab(command);
	command->bin = get_absolute_path(z, command->cmd_tab[0]);
	command->token = lst_token_first(command->token);
	if (command->bin)
	{
		g_exitg.exit = execve(command->bin, command->cmd_tab, z->env);
		handle_errno(z, command->token->word, errno);
	}
	else if (g_exitg.exit != 126)
		handle_errno(z, command->token->word, 14);
	return (0);
}
