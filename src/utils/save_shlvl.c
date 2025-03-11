/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_shlvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:04:01 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/23 15:16:01 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_new_shlvl(t_mini *mini)
{
	char	*shlvl_str;
	char	*new_shlvl;

	shlvl_str = ft_itoa(ft_atoi(ft_getenv("SHLVL", mini->env)) + 1);
	new_shlvl = ft_strjoin("SHLVL=", shlvl_str);
	free(shlvl_str);
	return (new_shlvl);
}

void	save_shlvl(t_mini *mini)
{
	char	**new_env;
	int		len;
	int		i;
	int		j;

	len = ft_arrlen(mini->env);
	new_env = malloc((len + 1) * sizeof(char *));
	if (!new_env)
		error(mini, 'M');
	i = 0;
	j = 0;
	while (i < len)
	{
		if (ft_strncmp(mini->env[i], "SHLVL=", 6) == 0)
			new_env[j++] = create_new_shlvl(mini);
		else
			new_env[j++] = ft_strdup(mini->env[i]);
		i++;
	}
	new_env[j] = NULL;
	ft_freearr(mini->env);
	mini->env = new_env;
}
