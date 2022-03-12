/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 09:20:54 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/23 23:35:57 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	*lst_builtin_new(void)
{
	t_builtin	*new;

	new = malloc(sizeof(t_builtin));
	if (!new)
		shell_exit(1, "lst_builtin_new");
	ft_bzero(new, sizeof(t_builtin));
	return (new);
}

void	init_env(t_data *z, char **envp)
{
	char	*cwd;
	char	**path;

	z->env = ft_array_dup(envp);
	cwd = malloc(sizeof(char) * 4096);
	if (!cwd)
		shell_exit(1, "init_env");
	getcwd(cwd, 4096);
	z->pwd = ft_strdup(cwd);
	free(cwd);
	path = getmypath(z);
	if (!path)
		update_to_env(z, "PATH=", \
"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:", 2);
	else
		ft_free_array(path);
	update_to_env(z, "PWD=", z->pwd, 2);
	update_to_env(z, "_=", "/usr/bin/env", 2);
	update_pwd(z, 0);
	z->export = print_declarex_util(z);
}

void	init_shell(char **av, char **envp, t_data *z)
{
	int			fd;
	t_exitg		exitg;

	(void)av;
	if (read(0, NULL, 0) == -1)
		exit(0);
	fd = dup(0);
	if (fd == -1)
		exit(0);
	close(fd);
	ft_bzero(z, sizeof(t_data));
	ft_bzero(&exitg, sizeof(t_exitg));
	g_exitg = exitg;
	g_exitg.exit = 0;
	z->builtin = lst_builtin_new();
	init_env(z, envp);
	z->hist = init_hist(z);
	export_shlvl(z);
	z->line = ft_strdup("");
}

int	main(int ac, char **av, char **envp)
{
	t_data	z;

	if (ac > 1)
	{
		ft_putstr_fd("minishell: error: no arguments allowed\n", 2);
		return (0);
	}
	init_shell(av, envp, &z);
	signal(SIGINT, signal_check);
	signal(SIGQUIT, signal_check);
	if (isatty(0))
		read_line_tc(&z);
	ft_putstr_fd("minishell: error: need tty terminal\n", 2);
	return (0);
}
