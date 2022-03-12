/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_delstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 11:53:23 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/24 10:21:50 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** the function will del the line corresponding to str, returning the new array
*/

char	**ft_array_delstr(char **array, char *delstr)
{
	int		i;
	int		j;
	char	**ret;

	i = 0;
	while (array[i] && ft_strcmp(array[i], delstr))
		i++;
	if (i >= (int)ft_array_len(array))
		return (array);
	ret = (char **)malloc(sizeof(char *) * ft_array_len(array));
	if (!ret)
		ft_malloc_error_exit("ft_array_delstr");
	i = -1;
	j = 0;
	while (array[++i])
	{
		if (ft_strcmp(array[i], delstr))
			ret[j] = ft_strdup(array[i]);
		else
			j--;
		j++;
	}
	ret[j] = NULL;
	ft_free_array(array);
	return (ret);
}
