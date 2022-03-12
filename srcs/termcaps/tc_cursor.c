/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_cursor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 12:25:39 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/24 12:36:09 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cursor_position(int *col, int *rows)
{
	int		a;
	int		i;
	char	buff[255];
	int		ret;

	a = 0;
	i = 1;
	write(0, "\033[6n", 4);
	ret = read(0, buff, 254);
	buff[ret] = '\0';
	while (buff[i])
	{
		if (ft_isdigit(buff[i]))
		{
			if (a == 0)
				*rows = ft_atoi(&buff[i]) - 1;
			else
				*col = ft_atoi(&buff[i]) - 1;
			a++;
			i += ft_int_size(*col) - 1;
		}
		i++;
	}
	return (*col);
}

void	reset_curs_pos(t_data *z)
{
	int	i;

	i = get_col_len(z) - z->cursor->curcol;
	while (i-- > 0)
		tputs(tgetstr("le", NULL), 1, termcaps_putchar);
}

void	move_cursor(t_data *z, int mode)
{
	if (!mode && z->cursor->curcol > z->cursor->startcol)
	{
		tputs(tgetstr("le", NULL), 1, termcaps_putchar);
		z->cursor->curcol--;
	}
	if (mode && z->cursor->curcol
		< (int)(z->cursor->startcol + ft_strlen(z->hist->cur)))
	{
		tputs(tgetstr("nd", NULL), 1, termcaps_putchar);
		z->cursor->curcol++;
	}
}

int	get_col_len(t_data *z)
{
	int	ret;

	ret = 0;
	if (z->hist->cur)
		ret += ft_strlen(z->hist->cur);
	return (ret);
}
