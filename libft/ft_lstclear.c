/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jtrebes@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/22 08:53:48 by jim               #+#    #+#             */
/*   Updated: 2020/05/05 16:01:47 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*elem;

	if (!*lst || !lst)
		return ;
	elem = *lst;
	while (elem)
	{
		tmp = elem;
		elem = elem->next;
		(*del)(tmp->content);
		free(tmp);
	}
	*lst = NULL;
}
