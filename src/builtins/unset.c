/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:54:29 by jaimesan          #+#    #+#             */
/*   Updated: 2024/12/13 13:54:45 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset(t_token *token, t_mini *mini)
{
	char	**new_env;
	int		x;

	x = 1;
	g_status = 0;
	while (token->cmd[x])
	{
		if (find_env_variable(mini->env, token->cmd[x]) != NULL)
		{
			new_env = malloc(ft_arrlen(mini->env) * sizeof(char *));
			if (!new_env)
				return ;
			new_env = ft_new_env(mini, token->cmd[x], new_env);
			ft_freearr(mini->env);
			mini->env = new_env;
		}
		x++;
	}
}

char	**ft_new_env(t_mini *mini, char *str, char **new_env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ft_arrlen(mini->env))
	{
		if (ft_strncmp(mini->env[i], str,
				ft_strlen(str)) == 0
			&& mini->env[i][ft_strlen(str)] == '=')
		{
			i++;
			continue ;
		}
		new_env[j++] = ft_strdup(mini->env[i++]);
	}
	new_env[j] = NULL;
	return (new_env);
}

char	*find_env_variable(char **env, const char *key)
{
	int	i;
	int	key_len;

	i = 0;
	if (!env || !key)
		return (NULL);
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (env[i]);
		i++;
	}
	return (NULL);
}
