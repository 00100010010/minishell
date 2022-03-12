/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jtrebes@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 17:19:30 by jim               #+#    #+#             */
/*   Updated: 2020/04/28 21:49:57 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (i < dstsize)
	{
		if (dst[i] == '\0')
		{
			i = 0;
			len = ft_strlen(dst);
			while (src[i] && i < (dstsize - len) - 1)
			{
				dst[len + i] = src[i];
				i++;
			}
			dst[len + i] = '\0';
			return (ft_strlen(src) + len);
		}
		i++;
	}
	return (dstsize + ft_strlen(src));
}
