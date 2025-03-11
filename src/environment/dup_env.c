/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:05:03 by ctommasi          #+#    #+#             */
/*   Updated: 2024/11/26 13:05:04 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_env(t_mini *mini, char **env)
{
	int	len;
	int	i;

	len = ft_arrlen(env);
	mini->env = malloc((len + 1) * sizeof(char *));
	if (!mini->env)
		return ;
	i = 0;
	while (i < len)
	{
		mini->env[i] = ft_strdup(env[i]);
		if (!mini->env[i])
			return ;
		i++;
	}
	mini->env[i] = NULL;
}
