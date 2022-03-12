/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:25:04 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/24 16:43:44 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_child(t_data *z, t_cmd *command)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &z->shellterm.saved);
	make_redir(z, command);
	if (is_built_in(command))
		exec_built_in(z, command);
	else if (command->in != -1 && command->out != -1)
		exec_built_out(z, command);
	condition_exec_cmds(z, command, 1);
	free_builtin(z);
	exit(g_exitg.exit);
}

pid_t	fork_child(int in, int out, int fd_to_close)
{
	pid_t	pid;

	pid = fork();
	if (!pid && out != STDOUT_FILENO)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
	if (!pid && in != STDIN_FILENO)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (!pid)
		close(fd_to_close);
	return (pid);
}

void	get_the_child_ready(t_cmd *cmd)
{
	if (cmd->prev_sep_type < 2 && cmd->sep_type == PIPE)
	{
		pipe(cmd->pipe);
		g_exitg.pid = fork_child(STDIN_FILENO, cmd->pipe[1], cmd->pipe[0]);
	}
	else if (cmd->prev_sep_type == PIPE && cmd->sep_type == PIPE)
	{
		pipe(cmd->pipe);
		g_exitg.pid = fork_child(cmd->prev->pipe[0],
				cmd->pipe[1], cmd->pipe[0]);
		close(cmd->prev->pipe[1]);
	}
	else if (cmd->prev_sep_type == PIPE
		&& (cmd->sep_type < 2 || cmd->next_sep_type == END))
	{
		pipe(cmd->pipe);
		g_exitg.pid = fork_child(cmd->prev->pipe[0],
				STDOUT_FILENO, cmd->pipe[0]);
		close(cmd->prev->pipe[1]);
		close(cmd->pipe[1]);
	}
	else
		g_exitg.pid = fork();
}

void	exec_cmd(t_data *z, t_cmd *command)
{
	int		status;

	status = 0;
	g_exitg.forked = 1;
	if (command->prev_sep_type == PIPE && command->sep_type == PIPE)
		get_the_child_ready(command);
	else if (command->prev_sep_type == PIPE
		&& (command->sep_type < 2 || command->next_sep_type == END))
		get_the_child_ready(command);
	else
		 get_the_child_ready(command);
	if (g_exitg.pid == 0)
		exec_child(z, command);
	if (command->next && command->sep_type == PIPE)
		exec_cmds(z, command->next);
	close_exec_fds(z, command);
	waitpid(g_exitg.pid, &status, WUNTRACED);
	while (!WIFEXITED(status))
		if (!WIFSIGNALED(status) || command->sep_type == PIPE || g_exitg.quit)
			break ;
	if (WIFEXITED(status) && command->sep_type != PIPE)
		g_exitg.exit = WEXITSTATUS(status);
	g_exitg.forked = 0;
	while (wait(&status) > 0)
		status = 0;
}

int	exec_cmds(t_data *z, t_cmd *command)
{
	ft_free_array(z->export);
	z->export = print_declarex_util(z);
	if (command->sep_type != END)
	{
		command = parser(z, command);
		if (!command)
			return (1);
		if (condition_exec_cmds(z, command, 0))
		{
			exec_built_in(z, command);
			if (g_exitg.exit == -1)
				return (1);
		}
		else
			exec_cmd(z, command);
		while (command->sep_type == PIPE)
			command = command->next;
		z->cmd = command;
	}
	return (0);
}
