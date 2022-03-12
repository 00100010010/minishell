/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 18:32:54 by jim               #+#    #+#             */
/*   Updated: 2021/05/24 12:36:16 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define SHELL_PROMPT_NAME "minishell"
# define SHELL_PROMPT_SYMBOL " \e[31m>\e[34m>\e[32m>\e[0m "
# define PROMPT_NAME_COLOR "red"
# define USER_TEXT_COLOR "green"
# define SHELL_TEXT_COLOR "blue"
# define SHELL_PATH_COLOR "red"
# define SEMILICON 1
# define PIPE 2
# define REDIR_IN 3
# define REDIR_OUT 4
# define REDIR_APPEN 5
# define BACKSPACE 127
# define EOF_KEY 4
# define CTRL_C 3
# define UP_ARROW 4283163
# define DOWN_ARROW 4348699
# define LEFT_ARROW 4479771
# define RIGHT_ARROW 4414235
# define CMD_PWD "pwd"
# define CMD_CD "cd"
# define CMD_ECHO "echo"
# define CMD_EXIT "exit"
# define CMD_ENV "env"
# define CMD_EXPORT "export"
# define CMD_UNSET "unset"
# define BUILTINS_COUNT 7
# define END 666
# include "../libft/includes/libft.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/errno.h>
# include <term.h>
# include <sys/ioctl.h>
# include <dirent.h>

typedef struct s_termios_minishell
{
	struct termios	saved;
	struct termios	raw;
}				t_termios_minishell;

typedef struct s_lines_lst
{
	char				*line;
	char				*bckp;
	struct s_lines_lst	*next;
	struct s_lines_lst	*prev;

}				t_lines_lst;

typedef struct s_hist
{
	char			*cur;
	char			*line_too_long;
	t_lines_lst		*lines_lst;
	int				mode;
}				t_hist;

typedef struct s_cursor
{
	char			*cm;
	int				row;
	int				col;
	int				curcol;
	int				startcol;
	int				overlinestr;
}				t_cursor;

typedef struct s_builtin
{
	char			*path;
	char			**cmd;
}				t_builtin;

typedef struct s_token
{
	char			*word;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_cmd
{
	struct s_token					*token;
	char							*full_cmd;
	char							**cmd_tab;
	int								sep_type;
	int								auto_dest;
	int								prev_sep_type;
	int								next_sep_type;
	int								in;
	int								out;
	int								pipe[2];
	char							*bin;
	char							*filename_in;
	char							*filename_out;
	struct s_cmd					*next;
	struct s_cmd					*prev;
}				t_cmd;

typedef struct s_data
{
	char							*line;
	t_builtin						*builtin;
	t_cursor						*cursor;
	t_hist							*hist;
	t_termios_minishell				shellterm;
	char							*pwd;
	char							*pwdbckp;
	int								pwd_del;
	char							*oldpwd;
	int								oldpwd_del;
	struct s_cmd					*cmd;
	char							**env;
	char							**export;
}				t_data;

typedef struct s_exitg
{
	int				quit;
	long long		exit;
	int				forked;
	pid_t			pid;
}				t_exitg;

t_exitg			g_exitg;
/////////////TOOLS
//TOOLS.c
int			is_condition_edge_pwd(t_data *z, char *pwd);
void		update_to_env(t_data *z, char *line_title,
				char *var_value, int mode);
char		*getmyenv(t_data *z, char *var_name);
void		export_shlvl(t_data *z);
void		shell_exit(int error_code, char *msg);
int			update_pwd(t_data *z, char *pwd);
//INIT.c
void		init_shell(char **av, char **envp, t_data *z);
void		init_lst(t_data *z, char *line, int k);
//INIT_TOOLS.c
int			get_winsize(void);
//SIGNALS.c
void		signal_check(int sig);
//LST CMD TOOLS.c
t_cmd		*lstcmd_putend(t_cmd *prev);
t_cmd		*lstcmd_delone(t_cmd *lst, int mode);
t_cmd		*lstcmd_first(t_cmd *lst);
t_cmd		*lstcmd_last(t_cmd *lst);
void		lstcmd_addback(t_cmd **alst, t_cmd *new);
t_cmd		*lstcmd_new(t_cmd *cmd);
//LST TOKEN TOOLS.c
t_token		*lst_token_putend(t_token *lst);
t_token		*lst_token_delone(t_token *lst, int mode);
t_token		*lst_token_first(t_token *lst);
t_token		*lst_token_last(t_token *lst);
void		lst_token_addback(t_token **alst, t_token *new);
t_token		*lst_token_new(t_token *token);
/////////////READLINE
//READLINE_MAIN.c
char		*read_line(t_data *z);
//READLINE_TOOLS.c
int			put_error_msg(char *line, int i);
void		add_line_history(t_data *z, char *line);
int			display_prompt(t_data *z);
int			has_invalid_param(char *line);
int			count_words(char *line);
int			has_empty_sep(char *line);
int			has_backslash_multiline(char *line);
int			has_open_brackets(char *line);
int			pos_is_in_bracket(char *line, int pos, int mode);
int			has_invalid_char(char *line);
int			has_expand_ansic_quoted(char *line);
int			has_invalid_expand_type(char *line);
int			has_no_redir(char *line);
/////////////PARSING
//PRE PARSING
void		pre_parsing(t_data *z, char *line);
//PRE PARSING TOOLS.c
int			is_sep(char *line, int pos);
int			next_end_cmd(char *line, int i);
//PARSING MAIN
t_cmd		*parser(t_data *z, t_cmd *command);
//PARSING TOOLS
int			check_ambigous_redir(t_data *z);
int			is_escaped(char *s, int pos);
t_cmd		*put_prevnext_type(t_cmd *cmd);
t_cmd		*clean_redir_tokens(t_data *z, t_cmd *cmd);
//PARSING EXPANDER
char		*expander_line(t_data *z, char *line);
t_cmd		*expander(t_data *z, t_cmd *cmd);
//PARSING EXPANDER TOOLS.c
char		*make_case(t_data *z, char *line, int i, int ret);
t_cmd		*delete_empty_expands(t_cmd *cmd);
char		*get_var_name(t_data *z, char *src, int pos, int mode);
char		*get_var_value(t_data *z, char *check_name);
//PARSING TOKENIZER
t_cmd		*tokenizer(t_cmd *cmd);
//PARSING REDIRECTIONS TOOLS
void		cpy_tokens(t_data *z, t_cmd *command);
t_cmd		*clean_redir_tokens2(t_data *z, t_cmd *command);
t_cmd		*init_new_cmd(t_data *z, t_cmd *command);
t_cmd		*clean_redir_in(t_data *z, t_cmd *command, int *ret);
t_cmd		*clean_redir_out(t_data *z, t_cmd *command, int *ret);
t_cmd		*clean_redir_appen(t_data *z, t_cmd *command, int *ret);
//PARSING CLEANER
t_cmd		*tokens_cleaner(t_cmd *cmd);
int			is_condition_clean(char *src, int pos, int mode);
//PARSING CLEANER TOOLS
int			*mark_single_quotes(char *line);
char		*clean_single_quotes(char *line, int *single_quotes_lst);
char		*clean_double_quotes(char *line);
char		*clean_backslash(char *line, int *backslash_lst);
int			*mark_backslash(char *line);
/////////////EXEC
//EXEC_MAIN.c
int			exec_cmds(t_data *z, t_cmd *cmd);
int			exec_built_in(t_data *z, t_cmd *cmd);
//EXEC_TOOLS.c
void		exit_util(t_data *z);
void		close_exec_fds(t_data *z, t_cmd *command);
void		free_builtin(t_data *z);
char		**getmypath(t_data *z);
int			exec_built_out(t_data *z, t_cmd *command);
void		handle_errno(t_data *z, char *cmd, int type);
void		close_fds(t_data *z, int mode);
int			make_redir(t_data *z, t_cmd *command);
char		**conv_cmd_to_tab(t_cmd *cmd);
char		*get_absolute_path(t_data *z, char *cmd_line);
int			is_built_in(t_cmd *cmd);
//////////BUILT_INS
int			builtin_pwd(t_data *z);
int			builtin_cd(t_data *z);
int			builtin_echo(t_data *z);
int			builtin_exit(t_data *z);
int			builtin_env(t_data *z);
int			builtin_export(t_data *z);
int			builtin_unset(t_data *z);
//EXPORTS_TOOLS
char		**print_declarex_util(t_data *z);
char		**split_export(char *line);
int			compar_sort(char *str1, char *str2);
char		**sort_tabenv(char **tabenv);
char		*add_quote_value(t_data *z, char *line);
int			is_valid_char(int mode, char *name, int pos, int flag);
int			export_error_message(t_data *z, char *name);
int			is_valid_name_export(t_data *z, char *name, int mode);
void		*write_export(t_data *z, char *line, int i, int mode);
int			if_invalid_get_next(t_data *z);
void		free_and_go_next(t_data *z, char *line, char **tab1);
//EXIT TOOLS
void		ft_atoi_custom_util(unsigned long long res,
				int sign, int *flag_max);
//////////TERMCAPS
//TERMCAPS_INIT.c
t_hist		*init_hist(t_data *z);
void		init_term(t_data *z);
//TERMCAPS_LOOP.c
int			termcaps_loop_util(t_data *z, int mode);
int			termcaps_loop(t_data *z);
//TERMCAPS READLINE
void		read_line_tc(t_data *z);
//TERMCAPS_TOOLS.c
void		handle_ctrl_c(t_data *z);
void		clean_line(t_data *z);
int			termcaps_putchar(int termcap);
int			get_curcol(t_data *z);
void		move_cursor(t_data *z, int mode);
char		*insert_char(t_data *z, char c);
char		*del_char(t_data *z);
//TERMCAPS_CURSOR.c
int			get_cursor_position(int *col, int *rows);
void		init_cursor(t_data *z);
int			get_col_len(t_data *z);
void		move_cursor(t_data *z, int mode);
void		reset_curs_pos(t_data *z);
//TERMCAPS_HIST.c
void		hist_enter(t_data *z);
void		hist_up(t_data *z, char c);
void		hist_down(t_data *z, char c);
//TERMCAPS_HIST_TOOLS.c
int			condition_exec_cmds(t_data *z, t_cmd *cmd, int mode);
void		delete_lst_util(t_lines_lst *lst);
t_lines_lst	*get_first_last(t_lines_lst *lst, int mode);
t_lines_lst	*new_hist_line(t_lines_lst *prev, t_lines_lst *next, char *line);
t_lines_lst	*delete_lst(t_lines_lst *lst, int mode);
t_lines_lst	*delete_last(t_lines_lst *lst);
void		del_hist(t_data *z);
#endif
