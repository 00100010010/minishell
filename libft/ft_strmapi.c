/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 09:18:20 by jim               #+#    #+#             */
/*   Updated: 2021/03/27 16:55:05 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*out;
	int		i;

	if (!s || !f)
		return (0);
	out = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (out == NULL)
		return (0);
	i = -1;
	while (s[++i])
		out[i] = f(i, s[i]);
	out[i] = '\0';
	return (out);
}
