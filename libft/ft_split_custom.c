/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_custom.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 10:12:23 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/18 18:05:59 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_split(char **out, int k)
{
	while (k >= 0)
		free(out[k--]);
	free(out);
	return ;
}

static int	ft_countwords(char *s, int (*valid_cond)(char *, int, int))
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] && valid_cond(s, i, 0))
		i++;
	if (s[i])
		count = 1;
	while (s[i++])
	{
		if (s[i] && valid_cond(s, i - 1, 0) && !valid_cond(s, i, 0))
			count++;
	}
	return (count);
}

static char	*ft_putwords(char **out, char *s, int *z,
	int (*valid_cond)(char *, int, int))
{
	char	*str;
	int		i;
	int		j;

	i = z[0];
	while (i--)
		s++;
	i = 0;
	while (s[i] && !valid_cond(s, i, 0))
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
	{
		ft_free_split(out, z[1]);
		return (0);
	}
	str[i] = '\0';
	j = -1;
	while (i > ++j)
		str[j] = s[j];
	return (str);
}

char	**ft_split_custom(char *s, int valid_cond(char *, int, int))
{
	char	**out;
	int		z[2];

	if (!s)
		return (0);
	out = (char **)malloc(sizeof(char *) * (ft_countwords(s, valid_cond) + 1));
	if (out == NULL)
		return (0);
	z[0] = 0;
	z[1] = 0;
	while (s[z[0]])
	{
		if (!valid_cond(s, z[0], 0))
		{
			out[z[1]] = ft_putwords(out, s, z, valid_cond);
			z[1]++;
		}
		while (s[z[0]] && !valid_cond(s, z[0], 0))
			z[0]++;
		while (s[z[0]] && valid_cond(s, z[0], 0))
			z[0]++;
	}
	out[z[1]] = 0;
	return (out);
}
