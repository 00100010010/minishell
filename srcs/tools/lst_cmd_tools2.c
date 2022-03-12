/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 22:59:50 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/21 14:36:19 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*lstcmd_putend(t_cmd *prev)
{
	t_cmd	*end_elem;

	end_elem = lstcmd_new(0);
	end_elem->sep_type = END;
	prev->next = end_elem;
	end_elem->prev = prev;
	end_elem->next = 0;
	return (end_elem);
}

t_cmd	*lstcmd_delone_utils(t_cmd *lst)
{
	if (lst->sep_type != END)
		lst->token = lst_token_first(lst->token);
	while (lst->token && lst->token->type != END)
		lst->token = lst_token_delone(lst->token, 1);
	if (lst->token)
		free(lst->token);
	if (lst->full_cmd)
		free(lst->full_cmd);
	if (lst->cmd_tab)
		ft_free_array(lst->cmd_tab);
	if (lst->bin)
		free(lst->bin);
	if (lst->filename_in)
		free(lst->filename_in);
	if (lst->filename_out)
		free(lst->filename_out);
	if (lst->in && lst->in != -1)
		close(lst->in);
	if (lst->out && lst->out != -1)
		close(lst->out);
	if (lst->pipe[0])
		close(lst->pipe[0]);
	if (lst->pipe[1])
		close(lst->pipe[1]);
	return (lst);
}

t_cmd	*lstcmd_delone(t_cmd *lst, int mode)
{
	t_cmd	*prev;
	t_cmd	*next;

	prev = NULL;
	next = NULL;
	if (!lst)
		return (lstcmd_new(lst));
	if (lst->next)
		next = lst->next;
	if (lst->prev)
		prev = lst->prev;
	lst = lstcmd_delone_utils(lst);
	free(lst);
	lst = NULL;
	if (mode == -1)
		return (prev);
	else if (mode == 1)
		return (next);
	else if (prev)
		return (prev);
	return (next);
}
