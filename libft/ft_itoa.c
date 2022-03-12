/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/19 08:45:19 by jim               #+#    #+#             */
/*   Updated: 2021/05/18 16:55:36 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_int_size(long long n)
{
	size_t		len;

	len = 0;
	if (!n)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(long long n)
{
	char	*str;
	int		neg;
	int		num_len;

	neg = 0;
	num_len = ft_int_size(n);
	if (n < 0)
	{
		num_len++;
		neg = 1;
		n = -n;
	}
	num_len = ft_int_size(n) + neg;
	str = malloc(sizeof(char) * (num_len + 1));
	if (!str)
		return (NULL);
	str[num_len] = '\0';
	while (num_len)
	{
		str[--num_len] = n % 10 + 48;
		n = n / 10;
	}
	if (neg)
		str[0] = '-';
	return (str);
}
