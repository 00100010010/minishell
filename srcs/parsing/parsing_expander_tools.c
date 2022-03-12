/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expander_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 15:16:05 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/24 00:22:12 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*delete_empty_expands(t_cmd *cmd)
{
	cmd->token = lst_token_first(cmd->token);
	while (cmd->token->type != END)
	{
		if (!ft_strlen(cmd->token->word))
			cmd->token = lst_token_delone(cmd->token, 1);
		else
			cmd->token = cmd->token->next;
	}
	cmd->token = lst_token_first(cmd->token);
	return (cmd);
}

char	*make_case(t_data *z, char *line, int i, int ret)
{
	char	*var_name;

	var_name = NULL;
	if (ret == 2)
		var_name = get_var_name(z, line, i, 1);
	else if (ret == 1)
		var_name = ft_strdup("$");
	else if (ret == 3)
		var_name = ft_strdup("?");
	else if (ret == 5)
		var_name = ft_strdup("~+");
	return (var_name);
}

char	*get_var_value_utils(t_data *z, char *check_name)
{
	int		k;
	int		i;
	char	*var_name;
	char	*var_value;

	i = 0;
	k = 0;
	while (z->env[k])
	{
		var_name = get_var_name(z, z->env[k], 0, 0);
		if (!ft_strncmp(var_name, check_name, ft_strlen(var_name)))
		{
			i = ft_strlen(var_name) + 1;
			var_value = ft_substr(z->env[k], i, ft_strlen(z->env[k]) - i);
			free(var_name);
			return (var_value);
		}
		free(var_name);
		k++;
	}
	return (NULL);
}

/*
** input : char *var_name
** output : char *var_value, "" if var_name doesnt exist
*/

char	*get_var_value(t_data *z, char *check_name)
{
	char	*var_value;

	var_value = NULL;
	if (!strcmp(check_name, "?"))
		return (ft_itoa(g_exitg.exit));
	else if (!strcmp(check_name, "PWD"))
		return (getmyenv(z, "PWD="));
	else if (!strcmp(check_name, "OLDPWD"))
		return (getmyenv(z, "OLDPWD="));
	else if (!strcmp(check_name, "~+"))
	{
		var_value = getmyenv(z, "PWD=");
		if (!var_value)
			var_value = ft_strdup(check_name);
		return (var_value);
	}
	var_value = get_var_value_utils(z, check_name);
	if (!var_value)
		var_value = ft_strdup("");
	return (var_value);
}

/*
** inputs: char *src + pos of $ if set to 1 or true start of name if set to 0
** output: char *dst, the name of the var
*/

char	*get_var_name(t_data *z, char *src, int pos, int mode)
{
	char	*var_name;
	int		pos_cpy;

	(void)z;
	if (mode)
	{
		pos++;
		if (src[pos] && (ft_isalpha(src[pos] || src[pos] == '_')))
			return (ft_strdup(""));
	}
	pos_cpy = pos;
	while (src[pos] && (ft_isalnum(src[pos]) || src[pos] == '_'))
		pos++;
	var_name = ft_substr(src, pos_cpy, pos - pos_cpy);
	return (var_name);
}
