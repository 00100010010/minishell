/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_hist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:05:08 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/24 12:44:52 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hist_up(t_data *z, char c)
{
	(void)c;
	if (!z->hist->lines_lst || !z->hist->lines_lst->prev)
		return ;
	z->hist->lines_lst = z->hist->lines_lst->prev;
	z->hist->cur = z->hist->lines_lst->line;
	z->hist->mode++;
	if ((z->cursor->overlinestr + get_col_len(z)) > (get_winsize() - 1))
	{
		ft_putstr_fd("\nline is too long... relax !", 2);
		handle_ctrl_c(z);
	}
}

void	hist_down(t_data *z, char c)
{
	(void)c;
	if (!z->hist->mode)
		return ;
	z->hist->lines_lst = z->hist->lines_lst->next;
	z->hist->cur = z->hist->lines_lst->line;
	z->hist->mode--;
	if ((z->cursor->overlinestr + get_col_len(z)) > (get_winsize() - 1))
	{
		ft_putstr_fd("\nline is too long... relax !", 2);
		handle_ctrl_c(z);
	}
}

void	dup_new_last(t_lines_lst *lst)
{
	t_lines_lst		*save;

	save = lst;
	lst = get_first_last(lst, 1);
	lst = new_hist_line(lst, 0, save->line);
	lst = save;
}

void	change_bckp(t_lines_lst *lst)
{
	if (lst->line)
		free(lst->line);
	lst->line = ft_strdup(lst->bckp);
}

void	hist_enter(t_data *z)
{
	t_lines_lst		*save;

	save = z->hist->lines_lst;
	if (!z->hist->mode && !z->hist->cur)
	{
		z->hist->lines_lst = delete_last(save);
		return ;
	}
	if (z->hist->mode)
	{
		delete_last(save);
		if (save->line)
			dup_new_last(save);
		change_bckp(save);
	}
	save = get_first_last(save, 1);
	if (save->line)
	{
		if (save->bckp)
			free(save->bckp);
		save->bckp = ft_strdup(save->line);
	}
	z->hist->lines_lst = save;
}
