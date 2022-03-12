/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 09:51:47 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/18 17:44:51 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_array_dup(char **array)
{
	char	**ret;
	int		i;
	int		k;

	if (!array)
		return (0);
	k = ft_array_len(array);
	if (!k)
		return (0);
	ret = (char **)malloc(sizeof(char *) * (k + 1));
	if (!ret)
		ft_malloc_error_exit("ft_array_dup");
	i = 0;
	while (i < k)
	{
		ret[i] = ft_strdup(array[i]);
		i++;
	}
	ret[k] = NULL;
	return (ret);
}
