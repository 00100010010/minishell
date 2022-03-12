/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tc_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:52:48 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/24 00:11:26 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hist	*init_hist(t_data *z)
{
	t_hist	*new;

	(void)z;
	new = malloc(sizeof(t_hist));
	if (!new)
		shell_exit(1, "init_hist");
	ft_bzero(new, sizeof(t_hist));
	new->line_too_long = ft_strdup("line is too long... nice try...");
	return (new);
}

void	init_cursor(t_data *z)
{
	z->cursor = malloc(sizeof(t_cursor));
	ft_bzero(z->cursor, sizeof(t_cursor));
}

void	init_term(t_data *z)
{
	char	*str;

	str = getmyenv(z, "TERM=");
	if (!str)
		str = ft_strdup("xterm");
	tgetent(NULL, str);
	free(str);
	tcgetattr(STDIN_FILENO, &z->shellterm.saved);
	init_cursor(z);
}
