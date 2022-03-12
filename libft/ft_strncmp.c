/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 16:50:17 by jim               #+#    #+#             */
/*   Updated: 2021/03/20 13:46:36 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	a;
	unsigned char	b;

	if (!n)
		return (0);
	while (*s1 && *s2 && *s1 == *s2 && n >= 1)
	{
		s1++;
		s2++;
		n--;
	}
	a = *s1;
	b = *s2;
	return (a - b);
}
