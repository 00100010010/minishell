/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 20:41:54 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/21 18:33:45 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_errno(t_data *z, char *command, int type)
{
	char	*output;
	char	*cpy;
	char	**path;

	cpy = ft_strjoin("minishell: ", command);
	output = ft_strjoin(cpy, ": ");
	free(cpy);
	if (type == 14)
		path = getmypath(z);
	if (type == 14 && !path)
		cpy = ft_strjoin(output, "Aucun fichier ou dossier de ce type");
	else if (type == 14)
	{
		ft_free_array(path);
		cpy = ft_strjoin(output, "command not found");
	}
	else
		cpy = ft_strjoin(output, strerror(errno));
	free(output);
	output = ft_strjoin(cpy, "\n");
	free(cpy);
	ft_putstr_fd(output, 2);
	free(output);
	g_exitg.exit = 127;
}

void	close_fds(t_data *z, int mode)
{
	if (mode)
		z->cmd = lstcmd_first(z->cmd);
	while (z->cmd->sep_type != END)
	{
		if (z->cmd->pipe[0])
			close(z->cmd->pipe[0]);
		if (z->cmd->pipe[1])
			close(z->cmd->pipe[1]);
		if (z->cmd->out)
			close(z->cmd->out);
		if (z->cmd->in)
			close(z->cmd->in);
		if (!mode)
			break ;
		z->cmd = z->cmd->next;
	}
}

int	make_redir(t_data *z, t_cmd *command)
{
	(void)z;
	if (command->auto_dest)
		return (0);
	if (command->filename_out)
	{
		dup2(command->out, STDOUT_FILENO);
		close(command->out);
	}
	if (command->filename_in)
	{
		dup2(command->in, STDIN_FILENO);
		close(command->in);
	}
	return (0);
}

char	**conv_cmd_to_tab(t_cmd *cmd)
{
	char	**cmd_tab;

	cmd_tab = NULL;
	cmd->token = lst_token_first(cmd->token);
	while (cmd->token->type != END)
	{
		cmd_tab = ft_array_addstr(cmd_tab, cmd->token->word);
		cmd->token = cmd->token->next;
	}
	return (cmd_tab);
}
