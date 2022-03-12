/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 12:30:54 by jtrebes           #+#    #+#             */
/*   Updated: 2021/03/18 12:34:38 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	ft_free_split(char **out, int k)
{
	while (k >= 0)
		free(out[k--]);
	free(out);
	return ;
}

static int	ft_countwords(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] && s[i] == c)
		i++;
	if (s[i])
		count = 1;
	while (s[i++] && s)
	{
		if (s[i - 1] == c && s[i] != c && s[i] != '\0')
			count++;
	}
	return (count);
}

static char	*ft_putwords(char **out, char const *s, char c, int k)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
	{
		ft_free_split(out, k);
		return (0);
	}
	str[i] = '\0';
	j = -1;
	while (i > ++j)
		str[j] = s[j];
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	int		k;

	if (!s)
		return (0);
	out = (char **)malloc(sizeof(char *) * (ft_countwords(s, c) + 1));
	if (out == NULL)
		return (0);
	k = 0;
	while (*s && s)
	{
		if (*s != c)
		{
			out[k] = ft_putwords(out, s, c, k);
			k++;
		}
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	out[k] = 0;
	return (out);
}
