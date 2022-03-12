/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:00:54 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/18 16:44:49 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_condition_clean(char *src, int pos, int mode)
{
	if (mode == 1 && src[pos] && src[pos] == 39 && !is_escaped(src, pos))
		if (!pos_is_in_bracket(src, pos, 2))
			return (1);
	if (mode == 2 && src[pos] && src[pos] == 34 && !is_escaped(src, pos))
		if (!pos_is_in_bracket(src, pos, 1))
			return (1);
	if (mode == 3 && src[pos] && src[pos] == '\\'
		&& !is_escaped(src, pos) && pos_is_in_bracket(src, pos, 2)
		&& src[pos + 1] && src[pos + 1] != 34 && src[pos + 1] != '$'
		&& src[pos + 1] != '\\')
		return (0);
	if (mode == 3 && src[pos] && src[pos] == '\\'
		&& !is_escaped(src, pos) && !pos_is_in_bracket(src, pos, 1))
		return (1);
	return (0);
}

t_cmd	*tokens_cleaner(t_cmd *cmd)
{
	int	*backslash_lst;
	int	*single_quotes_lst;

	cmd->token = lst_token_first(cmd->token);
	while (cmd->token->type != END)
	{
		backslash_lst = mark_backslash(cmd->token->word);
		single_quotes_lst = mark_single_quotes(cmd->token->word);
		cmd->token->word = clean_double_quotes(cmd->token->word);
		cmd->token->word = clean_single_quotes(cmd->token->word,
				single_quotes_lst);
		cmd->token->word = clean_backslash(cmd->token->word, backslash_lst);
		free(single_quotes_lst);
		free(backslash_lst);
		cmd->token = cmd->token->next;
	}
	cmd->token = lst_token_first(cmd->token);
	cmd = put_prevnext_type(cmd);
	return (cmd);
}
