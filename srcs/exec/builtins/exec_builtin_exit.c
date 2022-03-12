/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:07:33 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/24 14:49:38 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long	ft_atoi_custom(const char *str, int *flag_max)
{
	unsigned long long	res;
	int					sign;

	sign = 1;
	res = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str <= '9' && *str >= '0')
	{
		res = res * 10 + *str - '0';
		str++;
		ft_atoi_custom_util(res, sign, flag_max);
	}
	if ((*str && !ft_isdigit(*str)) || *flag_max == 2 || *flag_max == -1)
		return (0);
	return (res * sign);
}

long long	handle_exit_error_utils(char *line, int mode, int *flag_max)
{
	int	ret;

	if (!mode)
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(line, 2);
		ft_putstr_fd(" : argument numérique nécessaire\n", 2);
		ret = 2;
		if (*flag_max == 2)
			ret = 255;
	}
	else
		ret = -1;
	return (ret);
}

long long	hndle_ex_err(char **cm_ta, long long ret, int *flg_mx, char *cpy)
{
	int	i;

	i = -1;
	if (cpy && cm_ta[1][0] && cm_ta[1][0] == '-')
		i++;
	while (!ft_atoi_custom(cm_ta[1], flg_mx)
		&& !ret && cm_ta[1][++i] && *flg_mx != -1)
	{
		if ((i && !ft_isdigit(cm_ta[1][i]))
			|| (!i && !ft_isdigit(cm_ta[1][i]) && cm_ta[1][i] != '-')
			|| *flg_mx == 2)
			ret = handle_exit_error_utils(cm_ta[1], 0, flg_mx);
	}
	if (!ret && ft_array_len(cm_ta) > 2)
		ret = handle_exit_error_utils(cm_ta[1], 1, flg_mx);
	if (!ret && *flg_mx != 2)
		ret = ft_atoi_custom(cm_ta[1], flg_mx);
	else if (*flg_mx == 2)
		ret = 255;
	return (ret);
}

long long	handle_exit_num(char **cmd_tab)
{
	long long	ret;
	int			flag_max;
	char		*cpy;

	ret = 0;
	flag_max = 0;
	cpy = NULL;
	if (cmd_tab && ft_array_len(cmd_tab) >= 2)
	{
		if (ft_array_len(cmd_tab) >= 2)
			ret = hndle_ex_err(cmd_tab, ret, &flag_max, cpy);
		if (ft_array_len(cmd_tab) > 2 && ret == -1)
		{
			ft_putstr_fd("minishell: exit: trop d'arguments\n", 2);
			return (1);
		}
	}
	if (cmd_tab && cmd_tab[1]
		&& ft_atoi_custom(cmd_tab[1], &flag_max) && flag_max != 2)
	{
		cpy = ft_itoa(ft_atoi_custom(cmd_tab[1], &flag_max));
		free(cmd_tab[1]);
		cmd_tab[1] = cpy;
	}
	return (ret);
}

int	builtin_exit(t_data *z)
{
	if (!g_exitg.forked)
		ft_putstr_fd("exit\n", 1);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &z->shellterm.saved);
	if (z->cmd)
		g_exitg.exit = handle_exit_num(z->builtin->cmd);
	if (g_exitg.exit == -1)
		return (1);
	ft_put_color_fd("zero", 2);
	exit_util(z);
	exit(g_exitg.exit);
}
