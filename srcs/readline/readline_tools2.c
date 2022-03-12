/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_tools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:30:00 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/13 17:16:46 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_no_redir(char *line)
{
	int	i;
	int	flag;

	flag = 0;
	i = ft_strlen(line);
	while (--i >= 0)
	{
		if (is_sep(line, i) >= 2)
		{
			if (flag)
				return (flag);
			if (is_sep(line, i) == PIPE)
				ft_putstr_fd("OPEN PIPE OUT -> multiline \
bonus feature only\n", 2);
			else
				put_error_msg(line, i);
			return (0);
		}
		else if (!ft_isspace(line[i])
			|| (ft_isspace(line[i]) && is_escaped(line, i)))
			flag++;
	}
	return (1);
}

int	has_invalid_expand_type(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && !is_escaped(line, i)
			&& !pos_is_in_bracket(line, i, 1) && line[i + 1]
			&& ft_isdigit(line[i + 1]))
		{
			ft_putstr_fd("invalid $expansion follwed by \
a number is not supported\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	has_expand_ansic_quoted(char *line)
{
	int	k;
	int	flag;

	flag = 0;
	k = 0;
	while (line[k])
	{
		if (k && line[k] == 39 && line[k - 1] == '$'
			&& !is_escaped(line, k - 1) && !pos_is_in_bracket(line, k - 1, 0))
			flag++;
		k++;
	}
	if (flag)
		ft_putstr_fd("ANSI-C EXPANSION NOT SUPPORTED\n", 2);
	return (flag);
}

int	has_invalid_char(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isascii(line[i]))
		{
			ft_putstr_fd("NON-ASCII CHARACTERS\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	has_open_brackets(char *line)
{
	int	k;

	k = ft_strlen(line) - 1;
	if (!pos_is_in_bracket(line, k, 0))
		return (0);
	ft_putstr_fd("open brackets : unsupported feature : bonus only\n", 2);
	return (1);
}
