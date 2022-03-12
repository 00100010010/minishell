/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_addstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:53:23 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/25 10:23:34 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** the function will add str at the end of the array
*/

char	**ft_array_addstr(char **array, char *newstr)
{
	int		i;
	int		k;
	char	**ret;

	if (!array || !array[0])
	{
		array = (char **)malloc(sizeof(char *) * 1);
		array[0] = NULL;
	}
	k = ft_array_len(array);
	ret = (char **)malloc(sizeof(char *) * (k + 2));
	i = 0;
	while (array[i])
	{
		ret[i] = ft_strdup(array[i]);
		i++;
	}
	ret[i] = ft_strdup(newstr);
	ret[i + 1] = NULL;
	ft_free_array(array);
	return (ret);
}
