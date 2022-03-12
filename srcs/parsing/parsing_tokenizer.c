/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtrebes <jtrebes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 10:19:20 by jtrebes           #+#    #+#             */
/*   Updated: 2021/05/19 18:52:42 by jtrebes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_condition_tokenizer(char *src, int pos, int mode)
{
	if (src[pos] && src[pos] == ' '
		&& !is_escaped(src, pos) && !pos_is_in_bracket(src, pos, 0))
		return (1);
	return (0);
	(void)mode;
}

t_cmd	*tokenizer(t_cmd *cmd)
{
	char	**split;
	int		i;

	split = ft_split_custom(cmd->full_cmd, &is_condition_tokenizer);
	i = -1;
	while (split[++i])
	{
		lst_token_addback(&cmd->token, lst_token_new(cmd->token));
		cmd->token = lst_token_last(cmd->token);
		cmd->token->word = ft_strdup(split[i]);
	}
	lst_token_addback(&cmd->token, lst_token_new(cmd->token));
	cmd->token = lst_token_last(cmd->token);
	cmd->token->type = END;
	cmd->token = lst_token_first(cmd->token);
	ft_free_array(split);
	return (cmd);
}
