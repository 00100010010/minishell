/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:21:17 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/21 10:26:57 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*clean_redir_appen(t_data *z, t_cmd *command, int *ret)
{
	if (command->out)
		close(command->out);
	if (command->filename_out)
		free((char *)command->filename_out);
	if (!command->auto_dest)
		command->out = open(z->cmd->token->word,
				O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	if (command->out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(z->cmd->token->word, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_exitg.exit = 1;
		*ret = 0;
		close(command->out);
		z->cmd->out = -1;
		return (command);
	}
	command->filename_out = ft_strdup(z->cmd->token->word);
	g_exitg.exit = 0;
	*ret = 1;
	return (command);
}

t_cmd	*clean_redir_out(t_data *z, t_cmd *command, int *ret)
{
	if (command->out)
		close(command->out);
	if (command->filename_out)
		free((char *)command->filename_out);
	if (!command->auto_dest)
		command->out = open(z->cmd->token->word,
				O_CREAT | O_WRONLY | O_TRUNC | O_CLOEXEC, S_IRWXU);
	if (command->out == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(z->cmd->token->word, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_exitg.exit = 1;
		close(command->out);
		z->cmd->out = -1;
		*ret = 0;
		return (command);
	}
	command->filename_out = ft_strdup(z->cmd->token->word);
	g_exitg.exit = 0;
	*ret = 1;
	return (command);
}

t_cmd	*clean_redir_in(t_data *z, t_cmd *command, int *ret)
{
	if (command->in)
		close(command->in);
	if (command->filename_in)
		free((char *)command->filename_in);
	if (!command->auto_dest)
		command->in = open(z->cmd->token->word, O_RDONLY, S_IRWXU);
	if (command->in == -1 && !command->auto_dest)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(z->cmd->token->word, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_exitg.exit = 1;
		close(command->in);
		z->cmd->out = -1;
		*ret = 0;
		return (command);
	}
	command->filename_in = ft_strdup(z->cmd->token->word);
	g_exitg.exit = 0;
	*ret = 1;
	return (command);
}

t_cmd	*clean_redir_tokens2(t_data *z, t_cmd *command)
{
	int	ret;
	int	flag;

	ret = 1;
	z->cmd->token = lst_token_first(z->cmd->token);
	if (z->cmd->prev_sep_type == REDIR_IN)
		command = clean_redir_in(z, command, &ret);
	else if (ret && z->cmd->prev_sep_type == REDIR_OUT)
		command = clean_redir_out(z, command, &ret);
	else if (ret && z->cmd->prev_sep_type == REDIR_APPEN)
		command = clean_redir_appen(z, command, &ret);
	while (z->cmd->token->type != END)
		cpy_tokens(z, command);
	flag = 0;
	if (command->auto_dest)
		flag = 1;
	z->cmd = lstcmd_delone(z->cmd, 1);
	z->cmd->prev = command;
	command->next = z->cmd;
	if (z->cmd->auto_dest)
		command->auto_dest = 1;
	return (command);
}

t_cmd	*init_new_cmd(t_data *z, t_cmd *command)
{
	command = lstcmd_new(z->cmd->prev);
	if (command->prev)
		(*command->prev).next = command;
	return (command);
}
