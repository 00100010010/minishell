/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cleaner_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:00:54 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/18 17:48:54 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*mark_single_quotes(char *line)
{
	int	*single_quotes_lst;
	int	k;
	int	i;

	i = -1;
	k = 0;
	while (line[++i])
		if (line[i] == 39)
			k++;
	single_quotes_lst = malloc(sizeof(int) * k);
	if (!single_quotes_lst)
		shell_exit(1, "mark_single_quotes");
	k = 0;
	i = ft_strlen(line);
	while (i-- > 0)
	{
		if (is_condition_clean(line, i, 1))
			single_quotes_lst[k++] = 1;
		else if (line[i] == 39)
			single_quotes_lst[k++] = 0;
	}
	return (single_quotes_lst);
}

char	*clean_single_quotes(char *line, int *single_quotes_lst)
{
	int	i;
	int	k;

	k = 0;
	i = ft_strlen(line);
	while (i-- > 0)
		if (line[i] == 39)
			if (single_quotes_lst[k++])
				line = ft_strtrim_pos(line, i, i);
	return (line);
}

char	*clean_double_quotes(char *line)
{
	int	i;

	i = ft_strlen(line);
	while (i-- > 0)
		if (is_condition_clean(line, i, 2))
			line = ft_strtrim_pos(line, i, i);
	return (line);
}

char	*clean_backslash(char *line, int *backslash_lst)
{
	int	i;
	int	k;

	k = 0;
	i = ft_strlen(line);
	while (i-- > 0)
		if (line[i] == '\\')
			if (backslash_lst[k++])
				line = ft_strtrim_pos(line, i, i);
	return (line);
}

int	*mark_backslash(char *line)
{
	int	*backslash_lst;
	int	i;
	int	k;

	k = 0;
	i = -1;
	while (line[++i])
		if (line[i] == '\\')
			k++;
	backslash_lst = malloc(sizeof(int) * k);
	if (!backslash_lst)
		shell_exit(1, "mark_backslash");
	k = 0;
	i = ft_strlen(line);
	while (i-- > 0)
	{
		if (is_condition_clean(line, i, 3))
			backslash_lst[k++] = 1;
		else if (line[i] == '\\')
			backslash_lst[k++] = 0;
	}
	return (backslash_lst);
}
