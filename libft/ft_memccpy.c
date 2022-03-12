/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 07:49:49 by jtrebes           #+#    #+#             */
/*   Updated: 2021/03/18 12:30:21 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n-- > 0)
	{
		if (*(unsigned char *)dst == (unsigned char)c)
			return (dst);
		*(unsigned char *)dst++ = *(unsigned char *)src++;
	}
	return (0);
}
