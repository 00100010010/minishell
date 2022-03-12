/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 08:57:21 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/24 16:12:37 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** mode 0 = add ; mode 1 = replace ; mode 2 = both
*/

void	update_to_env(t_data *z, char *line_titl, char *var_value, int mode)
{
	int		i;
	char	*full_line;

	i = ft_array_strncmp(z->env, line_titl, ft_strlen(line_titl) - 1);
	full_line = ft_strjoin(line_titl, var_value);
	if ((mode == 2 && i == -1) || (!mode && i != -1))
		z->env = ft_array_addstr(z->env, full_line);
	else if (mode && i != -1)
		z->env = ft_array_replace_str_chr(z->env, z->env[i], full_line);
	free(full_line);
}

void	export_shlvl(t_data *z)
{
	char	*value;
	int		i;

	value = get_var_value(z, "SHLVL");
	if (!ft_strlen(value))
	{
		free(value);
		value = ft_strdup("0");
	}
	i = ft_atoi(value);
	i++;
	free(value);
	value = ft_itoa(i);
	update_to_env(z, "SHLVL=", value, 2);
	free(value);
}

static char	*getmyenv_utils(t_data *z, int i, char *var_name)
{
	char	*cpy;
	int		k;

	if (i == -1)
	{
		if (!ft_strcmp("PWD=", var_name))
			return (ft_strdup(z->pwd));
		if (!ft_strcmp("OLDPWD=", var_name))
			return (ft_strdup(z->oldpwd));
		return (NULL);
	}
	else if (i != -1)
	{
		k = 0;
		while (z->env[i][k] && z->env[i][k] != '=')
			k++;
		if (z->env[i][k] && z->env[i][k] == '=')
			k++;
		cpy = ft_substr(z->env[i], k, ft_strlen(z->env[i]) - k);
		return (cpy);
	}
	return (NULL);
}

char	*getmyenv(t_data *z, char *var_name)
{
	int		i;
	char	*cpy;

	if (var_name[ft_strlen(var_name) - 1] != '=')
	{
		cpy = ft_strjoin(var_name, "=");
		free(var_name);
		var_name = cpy;
	}
	i = ft_array_strncmp(z->env, var_name, ft_strlen(var_name) - 1);
	cpy = getmyenv_utils(z, i, var_name);
	return (cpy);
}
