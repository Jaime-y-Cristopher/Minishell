/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotations_commands_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:02:50 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/14 15:03:05 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_qouble_single_quotes(t_quote *q, int c)
{
	if (c == '\"' && !q->single_quote)
	{
		if (!q->escape)
		{
			q->double_quote = !q->double_quote;
			q->print = 0;
		}
		else
			q->print = 1;
		q->escape = 0;
		return (0);
	}
	if (c == '\'' && !q->double_quote)
	{
		if (!q->escape)
		{
			q->single_quote = !q->single_quote;
			q->print = 0;
		}
		else
			q->print = 1;
		q->escape = 0;
		return (0);
	}
	return (1);
}

int	get_escape_quotes(t_quote *q, int c, int c2)
{
	if (c == '\\')
	{
		if (q->escape)
		{
			q->print = 1;
			q->escape = 0;
		}
		else if (q->double_quote && (c2 == '\"' || c2 == '$' || c2 == '\\'))
		{
			q->print = 0;
			q->escape = 1;
		}
		else if (!q->double_quote && !q->single_quote)
		{
			q->print = 0;
			q->escape = 1;
		}
		else
		{
			q->print = 1;
			q->escape = 0;
		}
		return (0);
	}
	return (1);
}

void	get_quotes(t_quote *q, int c, int c2)
{
	if (!get_qouble_single_quotes(q, c))
		return ;
	if (!get_escape_quotes(q, c, c2))
		return ;
	if (c == '$' && ((q->double_quote && c2 == '\"')
			|| q->single_quote || q->escape || c2 == '/'))
	{
		q->expansion = 0;
		q->print = 1;
		return ;
	}
	else if (c == '$')
	{
		q->expansion = 1;
		q->print = 0;
		return ;
	}
	if (q->escape)
	{
		q->escape = 0;
		q->print = 1;
		return ;
	}
	q->print = 1;
}

int	check_valid_var(char *var_name)
{
	int	i;

	i = 1;
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i])
			|| var_name[i] != '_' || var_name[i] != '?')
			i++;
		else
			return (0);
	}
	return (1);
}
