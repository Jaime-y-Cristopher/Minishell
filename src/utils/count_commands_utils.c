/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:36:16 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/14 13:48:13 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_quote_type	get_quote(t_quote_type quote, char c)
{
	if (c == '\'')
	{
		if (quote == NO_QUOTE)
			return (SINGLE_QUOTE);
		else if (quote == SINGLE_QUOTE)
			return (NO_QUOTE);
	}
	else if (c == '\"')
	{
		if (quote == NO_QUOTE)
			return (DOUBLE_QUOTE);
		else if (quote == DOUBLE_QUOTE)
			return (NO_QUOTE);
	}
	return (quote);
}

static int	handle_quotes(const char *input, int *i, t_quote_type *quote)
{
	int	count;

	count = 1;
	*i += 1;
	while (input[*i] && *quote != NO_QUOTE)
	{
		*quote = get_quote(*quote, input[*i]);
		*i += 1;
	}
	return (count);
}

static int	handle_word(const char *input, int *i)
{
	int	count;

	count = 1;
	while (input[*i] && input[*i] != ' ' && !is_del(input[*i]))
	{
		*i += 1;
	}
	return (count);
}

static int	handle_delimiters(const char *input, int *i)
{
	int	count;

	count = 1;
	if ((input[*i] == '>' && input[*i + 1] == '>')
		|| (input[*i] == '<' && input[*i + 1] == '<'))
	{
		*i += 1;
	}
	*i += 1;
	return (count);
}

int	count_commands(t_mini *mini)
{
	int				i;
	int				count;
	t_quote_type	quote;

	i = 0;
	count = 0;
	quote = NO_QUOTE;
	while (mini->input[i])
	{
		quote = get_quote(quote, mini->input[i]);
		if (quote != NO_QUOTE)
			count += handle_quotes(mini->input, &i, &quote);
		else if (mini->input[i] != ' ' && !is_del(mini->input[i]))
			count += handle_word(mini->input, &i);
		else if (is_del(mini->input[i]))
			count += handle_delimiters(mini->input, &i);
		else if (mini->input[i] == ' ')
			i++;
	}
	return (count);
}
