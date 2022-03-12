/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 11:46:08 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/18 17:00:11 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* cut a string from pos start (inc) to end (inc)
** example : start = 1; end = 2;
** src = 1001 return = 11
*/

static char	*get_ret(int start, char *str1, char *str2)
{
	char	*ret;

	if (!start)
		ret = ft_strdup(str1);
	else
		ret = ft_strjoin(str2, str1);
	return (ret);
}

char	*ft_strtrim_pos(char *line, int start, int end)
{
	int		len;
	int		len_newline;
	char	*ret;
	char	*ret_cpy;
	char	*ret_cpy2;

	len = ft_strlen(line);
	len_newline = end - start;
	if (len == 1)
	{
		free(line);
		ret = ft_strdup("");
		return (ret);
	}
	if (!len_newline)
		len_newline = len - 1;
	ret_cpy2 = ft_substr(line, 0, start);
	ret_cpy = ft_substr(line, end + 1, len_newline);
	ret = get_ret(start, ret_cpy, ret_cpy2);
	free(ret_cpy);
	free(ret_cpy2);
	free(line);
	return (ret);
}
