/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 22:59:50 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/13 17:46:54 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lst_token_first(t_token *lst)
{
	if (!lst)
		return (0);
	while (lst->prev)
		lst = lst->prev;
	return (lst);
}

t_token	*lst_token_last(t_token *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	lst_token_addback(t_token **alst, t_token *new)
{
	if (!new)
		return ;
	if (!*alst)
	{
		new->prev = NULL;
		*alst = new;
		return ;
	}
	lst_token_last(*alst)->next = new;
	new->next = 0;
}

t_token	*lst_token_new(t_token *token)
{
	t_token	*new_elem;

	new_elem = malloc(sizeof(t_token));
	if (!new_elem)
		return (0);
	ft_bzero(new_elem, sizeof(t_token));
	if (token)
	{
		new_elem->prev = token;
		token->next = new_elem;
	}
	else
		new_elem->prev = 0;
	return (new_elem);
}
