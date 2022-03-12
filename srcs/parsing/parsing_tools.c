/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 21:45:58 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/19 12:45:47 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pos_is_in_bracket_utils(int bracket)
{
	if (bracket % 2 == 0)
		return (1);
	return (0);
}

int	pos_is_in_bracket(char *line, int pos, int mode)
{
	int	i;
	int	bracket_1;
	int	bracket_2;

	bracket_1 = 0;
	bracket_2 = 0;
	i = 0;
	while (i <= pos && line[i])
	{
		if (line[i] == 34 && !is_escaped(line, i))
			bracket_1 += pos_is_in_bracket_utils(bracket_2);
		else if (line[i] == 39 && !is_escaped(line, i))
			bracket_2 += pos_is_in_bracket_utils(bracket_1);
		else if (line[i] == 39 && is_escaped(line, i) && bracket_2 % 2 != 0)
			bracket_2 += pos_is_in_bracket_utils(bracket_1);
		i++;
	}
	if (mode == 1)
		return (bracket_2 % 2);
	else if (mode == 2)
		return (bracket_1 % 2);
	return ((bracket_1 % 2) + (bracket_2 % 2));
}

t_cmd	*put_prevnext_type(t_cmd *cmd)
{
	t_cmd	*next;
	t_cmd	*save;

	save = cmd;
	cmd = lstcmd_first(cmd);
	next = cmd->next;
	while (next->sep_type != END)
	{
		if (next->prev_sep_type == PIPE && cmd->sep_type != PIPE)
			cmd->sep_type = PIPE;
		cmd->next_sep_type = next->sep_type;
		next->prev_sep_type = cmd->sep_type;
		cmd = next;
		next = cmd->next;
	}
	cmd->next_sep_type = END;
	return (save);
}

int	is_escaped(char *s, int pos)
{
	int	escape;

	escape = 0;
	if (pos <= 0)
		return (0);
	while (pos > 0 && s[pos - 1] && s[pos - 1] == '\\'
		&& !pos_is_in_bracket(s, pos - 1, 1))
	{
		escape++;
		pos--;
	}
	return (escape % 2);
}
