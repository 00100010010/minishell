/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:00:08 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/24 12:37:47 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(t_data *z)
{
	ft_putstr_fd("^C\n", 2);
	g_exitg.exit = 130;
	z->cursor->overlinestr = 0;
	display_prompt(z);
	z->hist->lines_lst = delete_last(z->hist->lines_lst);
	if (z->hist->lines_lst && z->hist->lines_lst->line)
	{
		free(z->hist->lines_lst->line);
		z->hist->lines_lst->line = ft_strdup(z->hist->lines_lst->bckp);
	}
	z->hist->cur = NULL;
	termcaps_loop_util(z, 0);
}

char	*del_char(t_data *z)
{
	int		i;
	int		curs_pos_line;
	char	*ret;

	curs_pos_line = z->cursor->curcol - 1;
	if (ft_strlen(z->hist->lines_lst->line) == 1)
	{
		free(z->hist->lines_lst->line);
		return (NULL);
	}
	ret = malloc(sizeof(char) * ft_strlen(z->hist->lines_lst->line));
	if (!ret)
		shell_exit(1, "del_char");
	i = -1;
	while (++i < curs_pos_line)
		ret[i] = z->hist->lines_lst->line[i];
	while (z->hist->lines_lst->line[i + 1])
	{
		ret[i] = z->hist->lines_lst->line[i + 1];
		i++;
	}
	ret[i] = '\0';
	free(z->hist->lines_lst->line);
	return (ret);
}

char	*insert_char(t_data *z, char c)
{
	int		i;
	int		curs_pos_line;
	char	*ret;

	curs_pos_line = z->cursor->curcol;
	ret = malloc(sizeof(char) * (ft_strlen(z->hist->lines_lst->line) + 2));
	if (!ret)
		shell_exit(1, "insert_char");
	i = -1;
	while (++i < curs_pos_line)
		ret[i] = z->hist->lines_lst->line[i];
	ret[curs_pos_line] = c;
	while (z->hist->lines_lst->line[i])
	{
		ret[i + 1] = z->hist->lines_lst->line[i];
		i++;
	}
	ret[i + 1] = '\0';
	free(z->hist->lines_lst->line);
	return (ret);
}

void	clean_line(t_data *z)
{
	(void)z;
	tputs(tgetstr("cd", NULL), 2, termcaps_putchar);
}

int	termcaps_putchar(int termcap)
{
	write(2, &termcap, 1);
	return (0);
}
