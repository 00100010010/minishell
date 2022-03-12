/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 08:14:55 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/22 22:01:32 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*parser_utils2(t_data *z, t_cmd *command)
{
	while (command && command->token->type == END)
	{
		if (command->next_sep_type == END)
			return (NULL);
		command = command->next;
		command->full_cmd = expander_line(z, command->full_cmd);
		command = tokenizer(command);
		command = expander(z, command);
	}
	return (command);
}

t_cmd	*parser_utils(t_data *z, t_cmd *command)
{
	while (command->sep_type != END)
	{
		z->cmd = command;
		check_ambigous_redir(z);
		command->full_cmd = expander_line(z, command->full_cmd);
		if (!command->full_cmd)
			return (NULL);
		command = tokenizer(command);
		command = expander(z, command);
		command = parser_utils2(z, command);
		if (!command)
			return (NULL);
		command = tokens_cleaner(command);
		if (command->sep_type > 2)
			command = command->next;
		else
			break ;
	}
	return (command);
}

t_cmd	*parser(t_data *z, t_cmd *command)
{
	t_cmd	*save;

	save = command;
	command = parser_utils(z, command);
	if (!command)
		return (NULL);
	command = save;
	command = clean_redir_tokens(z, command);
	return (command);
}
