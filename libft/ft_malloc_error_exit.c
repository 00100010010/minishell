/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_error_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 16:23:53 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/18 17:45:33 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_malloc_error_exit(char *message)
{
	char	*output;

	output = ft_strjoin(message, ": malloc: error\n");
	ft_putendl_fd(output, 2);
	exit (1);
}
