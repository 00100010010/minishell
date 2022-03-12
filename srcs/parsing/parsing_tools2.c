/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 08:14:55 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/22 21:59:52 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_ambigous_error(char *str)
{
	char	*cpy;

	cpy = ft_strjoin("minishell: ", str);
	free(str);
	str = ft_strjoin(cpy, ": ambigous redirect\n");
	free(cpy);
	ft_putstr_fd(str, 2);
	free(str);
}

static int	check_ambigous_redir_util2(t_data *z, char **ret)
{
	int		i;
	char	*str;
	char	*cpy;

	i = 0;
	while (ret[i])
	{
		str = ft_strjoin(ret[i], "=");
		cpy = ft_substr(str, 1, ft_strlen(str) - 1);
		free(str);
		str = getmyenv(z, cpy);
		free(cpy);
		if (count_words(str))
		{
			free(str);
			ft_free_array(ret);
			return (0);
		}
		free(str);
		i++;
	}
	return (1);
}

static char	**check_ambigous_redir_util1(t_data *z)
{
	char	**ret;
	char	*var_name;
	char	*cpy;
	int		i;
	char	*str;

	str = z->cmd->full_cmd;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i] || str[i] != '$' || (str[i] == '$' && is_escaped(str, i)))
		return (0);
	ret = 0;
	while (i < (int)ft_strlen(str) && str[i] == '$')
	{
		var_name = get_var_name(z, str, i, 1);
		cpy = ft_strjoin("$", var_name);
		free(var_name);
		ret = ft_array_addstr(ret, cpy);
		i += ft_strlen(cpy);
		free(cpy);
	}
	return (ret);
}

static void	check_ambigous_redir_util3(t_data *z, char **ret)
{
	ft_free_array(ret);
	free(z->cmd->full_cmd);
	z->cmd->full_cmd = ft_strdup("weshhhh");
	g_exitg.exit = 1;
	z->cmd->auto_dest = 1;
}

int	check_ambigous_redir(t_data *z)
{
	int		i;
	char	*str;
	char	*cpy;
	char	**ret;

	if (z->cmd->prev_sep_type < 3 || z->cmd->prev_sep_type > 5)
		return (0);
	ret = check_ambigous_redir_util1(z);
	if (!ret)
		return (0);
	if (!check_ambigous_redir_util2(z, ret))
		return (0);
	i = 0;
	str = ft_strdup(ret[0]);
	while (ft_array_len(ret) > 1 && ret[++i])
	{
		cpy = ft_strjoin(str, ret[i]);
		free(str);
		str = ft_strdup(cpy);
		free(cpy);
	}
	print_ambigous_error(str);
	check_ambigous_redir_util3(z, ret);
	return (1);
}
