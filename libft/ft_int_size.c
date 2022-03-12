/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 16:39:57 by jtrebes           #+#    #+#             */
/*   Updated: 2021/03/18 12:21:42 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_int_size(int nbr)
{
	int	size;

	if (nbr < 0)
		nbr = -nbr;
	size = 0;
	while (nbr)
	{
		nbr /= 10;
		size++;
	}
	return (size);
}