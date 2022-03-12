/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token_tools2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 22:59:50 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/19 21:31:38 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lst_token_putend(t_token *lst)
{
	t_token	*end_elem;

	end_elem = lst_token_new(lst);
	end_elem->type = END;
	lst_token_addback(&lst, end_elem);
	lst = lst_token_first(lst);
	return (lst);
}

void	lst_token_delone_utils(t_token *lst, t_token *prev, t_token *next)
{
	if (lst->word)
		free(lst->word);
	free(lst);
	lst = NULL;
	if (next && prev)
	{
		next->prev = prev;
		prev->next = next;
	}
	else
	{
		if (next)
			next->prev = 0;
		if (prev)
			prev->next = 0;
	}
}

t_token	*lst_token_delone(t_token *lst, int mode)
{
	t_token	*prev;
	t_token	*next;

	prev = NULL;
	next = NULL;
	if (!lst)
		return (lst_token_new(lst));
	if (lst->next)
		next = lst->next;
	if (lst->prev)
		prev = lst->prev;
	lst_token_delone_utils(lst, prev, next);
	if (mode == -1)
		return (prev);
	else if (mode == 1)
		return (next);
	else if (!mode)
		return (next);
	else if (prev)
		return (prev);
	return (next);
}
