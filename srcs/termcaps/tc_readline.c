/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 15:55:30 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/21 11:09:35 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_line_tc_util2(t_data *z)
{
	pre_parsing(z, z->line);
	z->cmd = lstcmd_first(z->cmd);
	while (z->cmd->sep_type != END)
	{
		if (exec_cmds(z, z->cmd) && !z->cmd->next)
			break ;
		while (z->cmd->sep_type >= 2
			&& z->cmd->next_sep_type != END)
			z->cmd = z->cmd->next;
		z->cmd = z->cmd->next;
	}
	if (z->cmd)
	{
		z->cmd = lstcmd_first(z->cmd);
		while (z->cmd->next)
			z->cmd = lstcmd_delone(z->cmd, 1);
		free(z->cmd);
		z->cmd = NULL;
	}
}

static void	read_line_tc_util1(t_data *z)
{
	free(z->line);
	z->line = NULL;
	z->hist->cur = NULL;
	display_prompt(z);
	z->shellterm.raw = z->shellterm.saved;
	z->shellterm.raw.c_lflag &= ~(ICANON | ECHO | ISIG);
	z->shellterm.raw.c_cc[VMIN] = 1;
	z->shellterm.raw.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &z->shellterm.raw);
}

void	read_line_tc(t_data *z)
{
	int	ret;

	init_term(z);
	while (1)
	{
		read_line_tc_util1(z);
		if (termcaps_loop(z))
		{
			ft_put_color_fd(SHELL_TEXT_COLOR, 2);
			ret = has_invalid_param(z->line);
			if (ret && ret != 666)
				g_exitg.exit = ret;
			else if (!ret)
				read_line_tc_util2(z);
			g_exitg.forked = 0;
		}
	}
}
