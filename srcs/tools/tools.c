/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 08:57:21 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/23 23:44:06 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_winsize(void)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return (w.ws_col);
}

int	display_prompt(t_data *z)
{
	(void)z;
	ft_put_color_fd(SHELL_PATH_COLOR, 2);
	if (g_exitg.exit)
		ft_put_color_fd("red", 2);
	else
		ft_put_color_fd("green", 2);
	ft_putstr_fd(SHELL_PROMPT_NAME, 2);
	ft_putstr_fd(SHELL_PROMPT_SYMBOL, 2);
	ft_put_color_fd(USER_TEXT_COLOR, 2);
	return (0);
}

void	shell_exit(int error_code, char *msg)
{
	if (error_code == 1)
		ft_malloc_error_exit(msg);
}
