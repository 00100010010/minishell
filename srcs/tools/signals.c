/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:09:09 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/20 11:37:14 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_check(int sig)
{
	if (sig == SIGINT)
	{
		if (g_exitg.forked)
		{
			ft_putstr("\n");
			g_exitg.exit = 130;
		}
		else
			ft_putstr("\n");
		g_exitg.quit = 1;
	}
	if (sig == SIGQUIT)
	{
		if (g_exitg.forked)
		{
			ft_putendl_fd("Quiter (core dumped)", 1);
			g_exitg.exit = 131;
			g_exitg.quit = 4;
		}
	}
}
