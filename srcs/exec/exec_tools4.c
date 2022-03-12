/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:25:04 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/24 15:57:30 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	condition_exec_cmds_util(t_cmd *command)
{
	if (command->in)
	{
		close(command->in);
		command->in = -1;
		free(command->filename_in);
		command->filename_in = NULL;
	}
	if (command->out)
	{
		close(command->out);
		command->out = -1;
		free(command->filename_out);
		command->filename_out = NULL;
	}
	return (1);
}

int	condition_exec_cmds(t_data *z, t_cmd *command, int mode)
{
	command->token = lst_token_first(command->token);
	if (!mode && !command->out && !command->in && command->sep_type != PIPE
		&& command->prev_sep_type != PIPE && is_built_in(command))
		return (1);
	else if (!mode && (command->out || command->in) && command->token
		&& command->token->word && command->sep_type != PIPE
		&& (!ft_strcmp("export", command->token->word)
			|| !ft_strcmp("unset", command->token->word))
		&& command->token->next->type != END)
		return (1);
	else if (!mode && !ft_strcmp("exit", command->token->word)
		&& (command->in || command->out) && command->prev_sep_type != PIPE
		&& command->sep_type != PIPE)
		return (condition_exec_cmds_util(command));
	else if (mode == 1)
	{
		if (command->prev_sep_type < 2 && command->sep_type == PIPE)
			close_fds(z, 1);
		else if (command->prev_sep_type == PIPE && command->sep_type == PIPE)
			close_fds(z, 1);
		else if (command->prev_sep_type == PIPE
			&& (command->sep_type < 2 || command->next_sep_type == END))
			close_fds(z, 1);
	}
	return (0);
}
