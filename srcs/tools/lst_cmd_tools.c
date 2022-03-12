/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 22:59:50 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/16 13:09:47 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*lstcmd_first(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}

t_cmd	*lstcmd_last(t_cmd *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lstcmd_addback(t_cmd **alst, t_cmd *new)
{
	if (!new)
		return ;
	if (!*alst)
	{
		new->prev = NULL;
		*alst = new;
		return ;
	}
	lstcmd_last(*alst)->next = new;
	new->next = 0;
}

t_cmd	*lstcmd_new(t_cmd *cmd)
{
	t_cmd	*new_elem;

	new_elem = malloc(sizeof(t_cmd));
	if (!new_elem)
		return (0);
	ft_bzero(new_elem, sizeof(t_cmd));
	if (cmd)
		new_elem->prev = cmd;
	else
		new_elem->prev = 0;
	return (new_elem);
}
