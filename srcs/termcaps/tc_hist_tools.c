/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_hist_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:05:08 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/18 18:52:24 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lines_lst	*delete_last(t_lines_lst *lst)
{
	t_lines_lst	*prev;

	lst = get_first_last(lst, 1);
	prev = delete_lst(lst, 0);
	if (prev)
		prev->next = 0;
	return (prev);
}

t_lines_lst	*delete_lst(t_lines_lst *lst, int mode)
{
	t_lines_lst	*prev;
	t_lines_lst	*next;

	if (!lst)
		return (0);
	prev = lst->prev;
	next = lst->next;
	delete_lst_util(lst);
	if (lst->bckp)
		free(lst->bckp);
	if (lst->line)
		free(lst->line);
	free(lst);
	if (!mode && prev)
		return (prev);
	else if (next && mode)
		return (next);
	else
		return (0);
}

t_lines_lst	*get_first_last(t_lines_lst *lst, int mode)
{
	if (!lst)
		return (NULL);
	if (!mode)
		while (lst->prev)
			lst = lst->prev;
	else
		while (lst->next)
			lst = lst->next;
	return (lst);
}

t_lines_lst	*new_hist_line(t_lines_lst *prev, t_lines_lst *next, char *line)
{
	t_lines_lst	*new;

	new = malloc(sizeof(t_lines_lst));
	if (!new)
		shell_exit(1, "new_hist_line");
	ft_bzero(new, sizeof(t_lines_lst));
	if (prev)
	{
		new->prev = prev;
		prev->next = new;
	}
	if (next)
	{
		new->next = next;
		next->prev = new;
	}
	if (line)
	{
		new->line = ft_strdup(line);
	}
	return (new);
}

void	del_hist(t_data *z)
{
	z->hist->lines_lst = get_first_last(z->hist->lines_lst, 1);
	while (z->hist->lines_lst)
	{
		z->hist->lines_lst = delete_lst(z->hist->lines_lst, 0);
	}
	free(z->hist->line_too_long);
	free(z->hist);
	z->hist = NULL;
}
