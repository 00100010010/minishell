/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:12:36 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/18 17:23:58 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** will write all char * from the array. Separate by separator. Finished by a
** separator if flag is enabled
*/

void	ft_put_array(char **array, char *separator, int separator_flag)
{
	int		i;

	i = 0;
	while (array[i])
	{
		ft_putstr(array[i]);
		if (array[i + 1])
			ft_putstr(separator);
		i++;
	}
	if (separator_flag)
		ft_putstr(separator);
}
