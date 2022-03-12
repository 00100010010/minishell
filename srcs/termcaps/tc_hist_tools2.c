/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_hist_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:05:08 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/18 18:04:03 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_lst_util(t_lines_lst *lst)
{
	if (lst->next && lst->prev)
	{
		lst->next->prev = lst->prev;
		lst->prev->next = lst->next;
	}
	if (lst->prev && !lst->next)
		lst->prev->next = 0;
	if (lst->next && !lst->prev)
		lst->next->prev = 0;
}
