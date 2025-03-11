/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:10:19 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/26 12:00:52 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export(t_mini *mini, t_token *token)
{
	int		n;
	int		pos;

	if (!token->cmd[1])
		return (sort_export(mini));
	n = 1;
	pos = -1;
	while (token->cmd[n])
	{
		if (check_valid_export(token, n))
			return ;
		pos = export_exists(mini, token, n);
		if (pos == -2)
			return ;
		else if (pos == -1)
			new_export(mini, token, n);
		else
		{
			free(mini->env[pos]);
			mini->env[pos] = ft_strdup(token->cmd[n]);
		}
		pos = -1;
		n++;
	}
}

int	check_valid_export(t_token *token, int n)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	if (!token->cmd[n])
		return (1);
	while (token->cmd[n][i] != '=')
	{
		if (i == 0 && ft_isdigit(token->cmd[n][i]))
		{
			check = 1;
			break ;
		}
		else if (!(ft_isalnum(token->cmd[n][i]) || token->cmd[n][i] == '_'))
		{
			check = 1;
			break ;
		}
		i++;
	}
	if (token->cmd[n][i] == '=' && !check)
		return (0);
	write(2, "export: Bad Assignment!\n", 24);
	return (1);
}

int	export_exists(t_mini *mini, t_token *token, int n)
{
	int		i;
	int		len;
	char	*var_name;

	i = 0;
	while (token->cmd[n][i] && token->cmd[n][i] != '=')
		i++;
	var_name = malloc(i + 1 * sizeof(char));
	if (!var_name)
		return (-1);
	ft_strlcpy(var_name, token->cmd[n], i + 1);
	i = 0;
	len = ft_strlen(var_name);
	while (i < ft_arrlen(mini->env))
	{
		if (!ft_strncmp(mini->env[i], var_name, len)
			&& mini->env[i][ft_strlen(var_name)] == '=')
			return (free(var_name), i);
		i++;
	}
	return (free(var_name), -1);
}

void	new_export(t_mini *mini, t_token *token, int n)
{
	char	**new_env;
	int		len;
	int		i;

	len = ft_arrlen(mini->env);
	new_env = malloc((len + 2) * sizeof(char *));
	if (!new_env)
		return ;
	i = 0;
	while (i < len)
	{
		new_env[i] = ft_strdup(mini->env[i]);
		i++;
	}
	new_env[len] = ft_strdup(token->cmd[n]);
	new_env[len + 1] = NULL;
	ft_freearr(mini->env);
	mini->env = new_env;
}

void	sort_export(t_mini *mini)
{
	int		i;
	int		j;
	char	**sorted;
	int		len;

	sorted = ft_arrdup(mini->env);
	len = ft_arrlen(sorted);
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len - i - 1)
		{
			if (ft_strcmp(sorted[j], sorted[j + 1]) > 0)
				ft_swap(&sorted[j], &sorted[j + 1]);
			j++;
		}
		i++;
	}
	i = 0;
	while (sorted[i])
		printf("%s\n", sorted[i++]);
	ft_freearr(sorted);
}
