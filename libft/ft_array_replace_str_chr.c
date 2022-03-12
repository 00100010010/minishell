/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_replace_str_chr.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:34:23 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/15 10:15:10 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** the function will look to_replace string by char * newstr
*/

char	**ft_array_replace_str_chr(char **array, char *to_replace, char *newstr)
{
	int	i;
	int	flag;

	if (!array || !array[0])
		return (NULL);
	flag = 0;
	i = -1;
	while (array[++i] && !flag)
	{
		if (!ft_strcmp(array[i], to_replace))
		{
			flag++;
			free(array[i]);
			array[i] = ft_strdup(newstr);
		}
	}
	return (array);
}
