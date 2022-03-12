/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 20:30:00 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/22 21:53:34 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	edge_case(char *line, int i)
{
	if ((!i || ft_isspace(line[i - 1])) && line[i] == '~'
		&& line[i + 1] && line[i + 1] == '+')
	{
		if (!line[i + 2])
			return (5);
		if (line[i + 2] && (ft_isspace(line[i + 2]) || line[i + 2] == '/'))
			return (5);
	}
	if (line[i] != '$' || (line[i] == '$'
			&& (is_escaped(line, i) || pos_is_in_bracket(line, i, 1))))
		return (0);
	if (!line[i + 1] || ft_isspace(line[i + 1]) || !ft_isalpha(line[i + 1]))
		if (line[i + 1] != '?' && line[i + 1] != '_')
			return (0);
	if (ft_isalpha(line[i + 1]) || line[i + 1] == '_')
		return (2);
	if (line[i + 1] == '?')
		return (3);
	return (1);
}

static char	*get_expanded_line(t_data *z, char *line, int *i, char *var_name)
{
	char	*line_start;
	char	*line_end;
	char	*line_cpy;
	char	*var_value;
	int		k;

	k = *i + ft_strlen(var_name) + 1;
	if (!ft_strcmp(var_name, "~+"))
		k--;
	var_value = get_var_value(z, var_name);
	line_start = ft_substr(line, 0, *i);
	*i = *i + ft_strlen(var_value);
	line_end = ft_substr(line, k, ft_strlen(line) - k);
	line_cpy = ft_strjoin(line_start, var_value);
	free(line_start);
	free(var_value);
	free(line);
	line = ft_strjoin(line_cpy, line_end);
	free(line_end);
	free(line_cpy);
	return (line);
}

char	*expander_line(t_data *z, char *line)
{
	char	*var_name;
	int		i;
	int		ret;

	i = 0;
	while (i < (int)ft_strlen(line))
	{
		while (line[i] && !edge_case(line, i))
			i++;
		if (!line[i])
			break ;
		ret = edge_case(line, i);
		var_name = make_case(z, line, i, ret);
		line = get_expanded_line(z, line, &i, var_name);
		free(var_name);
	}
	return (line);
}

t_cmd	*expander(t_data *z, t_cmd *cmd)
{
	(void)z;
	cmd->token = lst_token_first(cmd->token);
	cmd = delete_empty_expands(cmd);
	cmd = put_prevnext_type(cmd);
	return (cmd);
}
