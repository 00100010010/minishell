/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_export_tools1.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:07:33 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/21 18:36:15 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_export(char *line)
{
	char	**ret;
	int		i;

	i = -1;
	while (line[++i] && line[i] != '=')
		if (!line[i])
			return (NULL);
	if ((ft_strlen(line) - i) == 0)
	{
		ret = malloc(sizeof(char *) * 2);
		if (!ret)
			shell_exit(1, "split_export");
		ret[1] = NULL;
	}
	else
	{
		ret = malloc(sizeof(char *) * 3);
		if (!ret)
			shell_exit(1, "split_export");
		ret[1] = ft_substr(line, i + 1, ft_strlen(line) - i);
		ret[2] = NULL;
	}
	ret[0] = ft_substr(line, 0, i);
	return (ret);
}

int	compar_sort(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 > *str2)
			return (1);
		if (*str1 < *str2)
			return (0);
		str1++;
		str2++;
		if (!*str2 && *str1)
			return (1);
	}
	return (0);
}

char	**sort_tabenv(char **tabenv)
{
	char	**ret;
	char	*cpy;
	int		i;

	ret = malloc(sizeof(char *) * (ft_array_len(tabenv) + 1));
	if (!ret)
		shell_exit(1, "sort_tabenv");
	ret[ft_array_len(tabenv)] = NULL;
	i = -1;
	while (tabenv[++i])
		ret[i] = ft_strdup(tabenv[i]);
	i = 0;
	while (ret[i])
	{
		if (ret[i + 1] && compar_sort(ret[i], ret[i + 1]))
		{
			cpy = ret[i];
			ret[i] = ret[i + 1];
			ret[i + 1] = cpy;
			i = -1;
		}
		i++;
	}
	return (ret);
}

char	*add_quote_value(t_data *z, char *line)
{
	char	*var_value;
	char	*var_name;
	char	*cpy;
	char	*ret;

	var_name = get_var_name(z, line, 0, 0);
	var_value = get_var_value(z, var_name);
	cpy = ft_strjoin(var_name, "=\"");
	free(var_name);
	var_name = ft_strjoin(cpy, var_value);
	free(cpy);
	free(var_value);
	ret = ft_strjoin(var_name, "\"");
	free(var_name);
	return (ret);
}

char	**print_declarex_util(t_data *z)
{
	int		i;
	char	**tabret;
	char	**tabret2;
	char	*line1;

	tabret = sort_tabenv(z->env);
	tabret2 = malloc(sizeof(char *) * (ft_array_len(tabret) + 1));
	i = 0;
	while (tabret[i])
	{
		line1 = add_quote_value(z, tabret[i]);
		tabret2[i] = ft_strjoin("declare -x ", line1);
		free(line1);
		i++;
	}
	tabret2[i] = NULL;
	ft_free_array(tabret);
	return (tabret2);
}
