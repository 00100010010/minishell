/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 18:45:37 by jim               #+#    #+#             */
/*   Updated: 2021/05/18 17:22:32 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_char(char const *s1, char c)
{
	char	*s3;
	int		i;
	int		len;

	len = ft_strlen(s1) + 1;
	s3 = (char *)malloc(sizeof(char) * (len + 1));
	if (s3 == NULL)
		return (0);
	i = 0;
	if (len > 1)
	{
		while (*s1)
			s3[i++] = *s1++;
	}
	s3[i++] = c;
	s3[i] = '\0';
	return (s3);
}
