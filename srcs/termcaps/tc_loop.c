/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 16:16:38 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/24 12:45:16 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_line(t_data *z)
{
	tputs(tgetstr("rc", NULL), 2, termcaps_putchar);
	clean_line(z);
	ft_putstr_fd(z->hist->cur, 2);
	reset_curs_pos(z);
}

static void	print_key_util(t_data *z, long c, int mode)
{
	char	*tmp;

	if (!mode)
	{
		if (z->cursor->curcol == get_col_len(z))
		{
			if (!z->hist->lines_lst->line)
				z->hist->lines_lst->line = ft_strdup("");
			tmp = z->hist->lines_lst->line;
			z->hist->lines_lst->line = ft_strjoin_char(tmp, c);
			free(tmp);
		}
		else
			z->hist->lines_lst->line = insert_char(z, c);
		z->hist->cur = z->hist->lines_lst->line;
		z->cursor->curcol++;
		print_line(z);
	}
	if (mode)
	{
		z->hist->lines_lst->line = del_char(z);
		z->hist->cur = z->hist->lines_lst->line;
		z->cursor->curcol--;
		print_line(z);
	}
}

void	print_key(t_data *z, long c)
{
	if (ft_isprint(c) && ((get_col_len(z) + z->cursor->overlinestr)
			< (get_winsize() - 1)))
		print_key_util(z, c, 0);
	else if (c == BACKSPACE && z->cursor->curcol > z->cursor->startcol)
		print_key_util(z, c, 1);
	else if (c == UP_ARROW)
	{
		hist_up(z, c);
		z->cursor->curcol = get_col_len(z);
		print_line(z);
	}
	else if (c == DOWN_ARROW)
	{
		hist_down(z, c);
		z->cursor->curcol = get_col_len(z);
		print_line(z);
	}
	else if (c == LEFT_ARROW && z->cursor->curcol > z->cursor->startcol)
		move_cursor(z, 0);
	else if (c == RIGHT_ARROW)
		move_cursor(z, 1);
}

int	termcaps_loop_util(t_data *z, int mode)
{
	int	a;

	if (!mode)
	{
		z->hist->mode = 0;
		z->hist->cur = NULL;
		z->cursor->startcol = get_col_len(z);
		z->cursor->curcol = z->cursor->startcol;
		z->hist->lines_lst = new_hist_line(z->hist->lines_lst, 0, 0);
		tputs(tgetstr("sc", NULL), 1, termcaps_putchar);
		get_cursor_position(&z->cursor->overlinestr, &a);
	}
	if (mode == 1)
	{
		ft_putstr_fd("\n", 2);
		z->cursor->overlinestr = 0;
		if (z->hist->cur)
		{
			z->line = ft_strdup(z->hist->lines_lst->line);
			return (1);
		}
	}
	return (0);
}

int	termcaps_loop(t_data *z)
{
	long	c;

	c = 0;
	termcaps_loop_util(z, 0);
	while (read(0, &c, sizeof(c)) > 0)
	{
		if (c == '\n')
		{
			hist_enter(z);
			break ;
		}
		if (c == EOF_KEY && !z->hist->cur)
			builtin_exit(z);
		if (c == CTRL_C)
			handle_ctrl_c(z);
		print_key(z, c);
		c = 0;
	}
	return (termcaps_loop_util(z, 1));
}
