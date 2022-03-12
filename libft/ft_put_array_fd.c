/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_array_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:10:16 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/18 16:56:45 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_array_fd(char **array,
	char *separator, int separator_flag, int fd)
{
	int		i;

	i = 0;
	while (array[i])
	{
		ft_putstr_fd(array[i], fd);
		if (array[i + 1])
			ft_putstr_fd(separator, fd);
		i++;
	}
	if (separator_flag)
		ft_putstr_fd(separator, fd);
}
