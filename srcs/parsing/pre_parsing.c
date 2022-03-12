/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 09:43:27 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/24 10:19:27 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_end_cmd(char *line, int i)
{
	while (line[i])
	{
		if (is_sep(line, i))
			return (i);
		i++;
	}
	return (i);
}

int	is_sep(char *line, int pos)
{
	if (!line[pos])
		return (0);
	if (line[pos] == ';' && !is_escaped(line, pos)
		&& !pos_is_in_bracket(line, pos, 0))
		return (SEMILICON);
	if (line[pos] == '|' && !is_escaped(line, pos)
		&& !pos_is_in_bracket(line, pos, 0))
		return (PIPE);
	if (line[pos] == '<' && !is_escaped(line, pos)
		&& !pos_is_in_bracket(line, pos, 0))
		return (REDIR_IN);
	if (line[pos] == '>' && !is_escaped(line, pos)
		&& !pos_is_in_bracket(line, pos, 0) && line[pos + 1]
		&& line[pos + 1] == '>')
		return (REDIR_APPEN);
	if (line[pos] == '>' && !is_escaped(line, pos)
		&& !pos_is_in_bracket(line, pos, 0))
		return (REDIR_OUT);
	return (0);
}

static t_cmd	*create_new_cmd(t_data *z, char *line, int *i)
{
	lstcmd_addback(&z->cmd, lstcmd_new(z->cmd));
	z->cmd = lstcmd_last(z->cmd);
	if (i[2] == END)
	{
		z->cmd->sep_type = END;
		z->cmd->prev_sep_type = i[2];
	}
	else
	{
		z->cmd->full_cmd = ft_substr(line, i[1], i[0] - i[1]);
		z->cmd->sep_type = is_sep(line, i[0]);
		z->cmd->prev_sep_type = i[2];
	}
	return (z->cmd);
}

void	pre_parsing(t_data *z, char *line)
{
	int		i[3];

	i[0] = 0;
	i[2] = 0;
	while (line[i[0]])
	{
		if (is_sep(line, i[0]))
		{
			i[2] = is_sep(line, i[0]);
			i[0]++;
			if (i[2] == REDIR_APPEN)
				i[0]++;
		}
		i[1] = i[0];
		i[0] = next_end_cmd(line, i[0]);
		if (!line[i[1]])
			break ;
		z->cmd = create_new_cmd(z, line, i);
		i[2] = 0;
	}
	i[2] = END;
	z->cmd = create_new_cmd(z, line, i);
}
