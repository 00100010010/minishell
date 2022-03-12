/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_strncmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:22:03 by jtrebes           #+#    #+#             */
/*   Updated: 2021/03/19 14:27:56 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** use strncmp in the full array, until something is found and return the line i
** else return (-1) if nothing
*/

int	ft_array_strncmp(char **array, char *str, size_t n)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (!ft_strncmp(array[i], str, n))
			return (i);
		i++;
	}
	return (-1);
}
