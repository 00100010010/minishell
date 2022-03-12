/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 14:21:17 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/21 18:31:59 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cpy_tokens(t_data *z, t_cmd *command)
{
	if (z->cmd->prev_sep_type > 2 && !z->cmd->token->prev)
		z->cmd->token = z->cmd->token->next;
	if (z->cmd->token->type == END)
		return ;
	if (command->token)
		command->token = lst_token_new(command->token);
	else
		command->token = lst_token_new(0);
	command->token->word = ft_strdup(z->cmd->token->word);
	z->cmd->token = z->cmd->token->next;
}

t_cmd	*clean_redir_tokens_utils2(t_data *z, int *flag, t_cmd *command)
{
	*flag = 0;
	while (!*flag && z->cmd->sep_type != END
		&& (z->cmd->sep_type > 2 || z->cmd->prev_sep_type > 2))
	{
		command = clean_redir_tokens2(z, command);
		if (!command)
			return (NULL);
		if (z->cmd->prev_sep_type < 3)
			*flag += 1;
	}
	if (command->token)
		lst_token_putend(command->token);
	if (!*flag && z->cmd->next)
		z->cmd = z->cmd->next;
	return (command);
}

int	clean_redir_tokens_utils1(t_data *z)
{
	while (z->cmd->sep_type != END
		&& z->cmd->sep_type < 3 && z->cmd->prev_sep_type < 3)
		z->cmd = z->cmd->next;
	if (z->cmd->sep_type == END)
		return (0);
	return (1);
}

t_cmd	*clean_redir_tokens(t_data *z, t_cmd *cmd)
{
	t_cmd	*command;
	int		flag;

	if (cmd->sep_type < 3 && cmd->prev_sep_type < 3)
		return (cmd);
	z->cmd = cmd;
	flag = 0;
	while (!flag && z->cmd->sep_type != END
		&& (z->cmd->sep_type > 2 || z->cmd->prev_sep_type > 2))
	{
		if (!clean_redir_tokens_utils1(z))
			break ;
		command = init_new_cmd(z, command);
		command = clean_redir_tokens_utils2(z, &flag, command);
		if (!command)
			return (NULL);
	}
	if (z->cmd->sep_type == END && !z->cmd->prev->token)
		return (NULL);
	command = put_prevnext_type(command);
	command->token = lst_token_first(command->token);
	while (command->token->type != END)
		command->token = command->token->next;
	return (command);
}
