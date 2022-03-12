/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 22:25:04 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/20 13:27:45 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_backslash_multiline(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	if (line[i] == '\\' && !is_escaped(line, i)
		&& !pos_is_in_bracket(line, i, 0))
	{
		ft_putstr_fd("cmd end with \\ : unsupported feature : bonus only\n", 2);
		return (1);
	}
	return (0);
}

int	has_invalid_param(char *line)
{
	if (!count_words(line))
		return (666);
	if (has_empty_sep(line))
		return (2);
	if (has_invalid_char(line))
		return (1);
	if (has_backslash_multiline(line))
		return (1);
	if (has_open_brackets(line))
		return (1);
	if (has_expand_ansic_quoted(line))
		return (1);
	if (has_invalid_expand_type(line))
		return (1);
	if (!has_no_redir(line))
		return (2);
	return (0);
}
