/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jtrebes@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/14 10:02:40 by jim               #+#    #+#             */
/*   Updated: 2020/05/02 11:04:55 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	while (*haystack && len > 0)
	{
		i = 0;
		while (haystack[i] && needle[i] && needle[i] == haystack[i] && i < len)
			i++;
		if (needle[i] == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	if (!*needle)
		return ((char *)haystack);
	return (0);
}
