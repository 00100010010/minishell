/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:30:00 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/21 18:28:54 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error_msg1(char *line, int i)
{
	int	x;
	int	k;

	while (line[i - 1] && (line[i - 1] == '>' || ft_isspace(line[i - 1])))
		i--;
	x = i;
	k = 0;
	while (line[x] && (line[x] == '>' || ft_isspace(line[x])))
	{
		x++;
		if (line[x] == '>')
			k++;
	}
	if (k < 3)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (k < 4)
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
	else
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
}

void	put_error_msg2(char *line, int i)
{
	int	x;

	x = i;
	while (line[x] && line[x] == '<')
		x++;
	if ((x - i) < 3)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if ((x - i) < 4)
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
	else if ((x - i) < 5)
		ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
	else
		ft_putstr_fd("syntax error near unexpected token `<<<'\n", 2);
}

int	put_error_msg(char *line, int i)
{
	if ((i && line[i - 1] && line[i - 1] == ';')
		|| (line[i + 1] && line[i + 1] == ';'))
		ft_putstr_fd("syntax error near unexpected token `;;'\n", 2);
	else if (line[i] == ';')
		ft_putstr_fd("syntax error near unexpected token `;'\n", 2);
	else if (line[i] == '>')
		put_error_msg1(line, i);
	else if (line[i] == '<')
		put_error_msg2(line, i);
	else if (line[i] == '|' && line[i + 1] && line[i + 1] == '|')
		ft_putstr_fd("syntax error near unexpected token `||'\n", 2);
	else if (line[i] == '|')
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	return (1);
}

int	has_empty_sep(char *line)
{
	int	i;
	int	flag;
	int	flag_next;

	flag_next = 0;
	flag = 0;
	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]) && !is_sep(line, i))
			flag++;
		if (!ft_isspace(line[i]) && !is_sep(line, i))
			flag_next = 0;
		if ((is_sep(line, i) && is_sep(line, i) < 3 && !flag && !flag_next)
			|| (is_sep(line, i) && flag_next && !flag))
			return (put_error_msg(line, i));
		else if (is_sep(line, i))
			flag = 0;
		if (is_sep(line, i) > 2)
			flag_next++;
		if (line[i] == '>' && line[i + 1] && line[i + 1] == '>')
			i++;
		i++;
	}
	return (0);
}

int	count_words(char *line)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		while (line[i] && ft_isspace(line[i]))
			i++;
		if (line[i] && !ft_isspace(line[i]))
			count++;
		while (line[i] && !ft_isspace(line[i]))
			i++;
	}
	return (count);
}
