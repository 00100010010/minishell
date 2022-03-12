/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_pwd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:07:33 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/21 10:20:53 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_data *z)
{
	char	*output;

	if (ft_strlen(z->pwd))
		output = ft_strjoin(z->pwd, "\n");
	else
		output = ft_strjoin(z->pwdbckp, "\n");
	ft_putstr_fd(output, 1);
	free(output);
	return (0);
}
