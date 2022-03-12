/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 16:53:31 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/18 16:54:34 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_color_fd(char *id, int fd)
{
	if (!ft_strcmp(id, "zero"))
		ft_putstr_fd("\e[0m", fd);
	if (!ft_strcmp(id, "red"))
		ft_putstr_fd("\e[31m", fd);
	if (!ft_strcmp(id, "blue"))
		ft_putstr_fd("\e[34m", fd);
	if (!ft_strcmp(id, "green"))
		ft_putstr_fd("\e[32m", fd);
	if (!ft_strcmp(id, "cyan"))
		ft_putstr_fd("\e[36m", fd);
}
