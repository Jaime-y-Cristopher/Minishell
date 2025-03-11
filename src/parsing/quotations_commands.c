/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotations_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:49:53 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/22 12:51:31 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotation(t_mini *mini)
{
	t_token	*token;
	t_quote	*q;

	q = malloc(sizeof(t_quote));
	if (!q)
		return (1);
	token = *(mini->commands);
	while (token != NULL)
	{
		if (token->cmd && !process_token(mini, q, token))
			return (free(q), 1);
		if (!token->is_builtin && !token->path && token->cmd != NULL)
			ft_check_path(token, mini);
		if (token->input_file && *token->input_file)
			token->input_file = remove_quotes(mini, q, token->input_file);
		if (token->output_file && *token->output_file)
			token->output_file = remove_quotes(mini, q, token->output_file);
		token = token->next;
	}
	return (free(q), 0);
}

int	process_token(t_mini *mini, t_quote *q, t_token *token)
{
	int	i;

	i = 0;
	while (token->cmd[i] != NULL)
	{
		token->cmd[i] = remove_quotes(mini, q, token->cmd[i]);
		if (q->single_quote || q->double_quote)
		{
			g_status = 1;
			return (write(2, "Error: Unclosed quotes\n", 23), 0);
		}
		if (is_builtin(token->cmd[0]))
			token->is_builtin = 1;
		i++;
	}
	return (1);
}

char	*remove_quotes(t_mini *mini, t_quote *q, char *cmd)
{
	char	*res;

	if (!cmd || !*cmd)
		return (cmd);
	res = ft_strdup("");
	init_quotes(q);
	res = process_quotes(mini, q, cmd, res);
	return (free(cmd), res);
}

char	*process_quotes(t_mini *mini, t_quote *q, char *cmd, char *res)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (cmd[i])
	{
		get_quotes(q, cmd[i], cmd[i + 1]);
		j = ft_strlen(res);
		if (q->print)
		{
			res = ft_realloc(res, j, j + 2);
			res[j++] = cmd[i];
			res[j] = '\0';
		}
		if (q->expansion)
		{
			temp = process_expansion(mini, q, cmd, &i);
			res = ft_strjoinf(res, temp);
			free(temp);
			continue ;
		}
		i++;
	}
	return (res);
}

char	*process_expansion(t_mini *mini, t_quote *q, char *cmd, int *i)
{
	char	*temp;
	int		k;

	temp = ft_strdup("$");
	(*i)++;
	k = 1;
	while (cmd[*i] && cmd[*i] != '\'' && cmd[*i] != '\"' && cmd[*i] != '$'
		&& cmd[*i] != '\\' && cmd[*i] != '/' && cmd[*i] != ' ')
	{
		temp = ft_realloc(temp, k, k + 2);
		temp[k++] = cmd[*i];
		temp[k] = '\0';
		if (cmd[*i - 1] && cmd[*i - 1] == '?' && ft_isascii(cmd[*i]))
			break ;
		(*i)++;
	}
	q->expansion = 0;
	if (check_valid_var(temp) && cmd[*i] != '\\'
		&& (cmd[*i] || cmd[(*i) - 1] == '?' || cmd[(*i) - 1] != '$'))
		temp = expand_variable(mini, temp);
	return (temp);
}
