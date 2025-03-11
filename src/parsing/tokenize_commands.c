/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 10:27:59 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/14 14:51:41 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_commands(t_mini *mini, char **cmds, t_token *cur)
{
	t_token	*token;

	token = cur;
	if (!cmds || !*cmds)
		return (1);
	if (!token || (token && token->complete))
	{
		token = ft_newtoken(NULL);
		ft_tokenadd_back(mini, token);
	}
	if (*cmds && !is_redirect(*cmds) && ft_strcmp(*cmds, "|"))
		cmds += tokenize_cmds(token, cmds);
	if (*cmds && is_redirect(*cmds))
	{
		if (tokenize_redirections(token, cmds, mini))
			return (1);
		cmds += 2;
	}
	if (*cmds && !ft_strcmp(*cmds, "|"))
	{
		if (tokenize_pipes(token, cmds))
			return (1);
		return (tokenize_commands(mini, ++cmds, NULL));
	}
	return (tokenize_commands(mini, cmds, token), 0);
}

int	tokenize_redirections(t_token *token, char **cmds, t_mini *mini)
{
	g_status = 0;
	if (*cmds && is_input_redirect(*cmds))
	{
		token->input_redir = ft_strdup(*cmds);
		cmds++;
		if (*cmds && !ft_strcmp(token->input_redir, "<<"))
			token->delimeter = ft_strdup(*cmds);
		else if (*cmds && !ft_strcmp(token->input_redir, "<"))
			token->input_file = ft_strdup(*cmds);
		else
			g_status = 1;
	}
	else if (*cmds && is_output_redirect(*cmds))
	{
		if (token->output_redir)
			free(token->output_redir);
		if (token->output_file)
			free(token->output_file);
		if (tokenize_redirections_utils(token, cmds, mini))
			g_status = 1;
	}
	if (g_status == 1)
		return (write(2, "Syntax error\n", 13), 1);
	return (0);
}

int	tokenize_redirections_utils(t_token *token, char **cmds, t_mini *mini)
{
	token->output_redir = ft_strdup(*cmds);
	cmds++;
	token->output_file = ft_strdup(*cmds);
	if (!token->output_file)
		return (1);
	if (ft_strchr(token->output_file, '$'))
		token->output_file = expand_variable(mini, token->output_file);
	if ((token->input_file && token->input_redir
			&& !access(token->input_file, F_OK)
			&& !access(token->input_file, X_OK)) || !token->input_redir)
	{
		mini->outfile = open(token->output_file, 00 | 0100 | 02000, 0644);
		close(mini->outfile);
	}
	else
	{
		g_status = 2;
		return (0);
	}
	free(token->output_file);
	if (*cmds)
		token->output_file = ft_strdup(*cmds);
	else
		return (1);
	return (0);
}

int	tokenize_pipes(t_token *token, char **cmds)
{
	token->pipe = ft_strdup(*cmds);
	cmds++;
	if (!(*cmds))
	{
		g_status = 2;
		return (write(2, "Syntax error\n", 13), 1);
	}
	token->complete = 1;
	return (0);
}

int	tokenize_cmds(t_token *token, char **cmds)
{
	int		old_len;
	int		new_len;
	char	**new_cmds;
	int		i;

	old_len = 0;
	new_len = 0;
	new_cmds = allocate_new_cmds(token, cmds, &old_len, &new_len);
	if (!new_cmds)
		return (-1);
	i = 0;
	while (i < new_len)
	{
		if (i < old_len)
			new_cmds[i] = ft_strdup(token->cmd[i]);
		if (i < new_len)
			new_cmds[i + old_len] = ft_strdup(cmds[i]);
		i++;
	}
	new_cmds[old_len + new_len] = NULL;
	if (token->cmd)
		ft_freearr(token->cmd);
	token->cmd = new_cmds;
	return (new_len);
}
