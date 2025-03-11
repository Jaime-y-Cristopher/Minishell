/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:30:04 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/20 17:30:06 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_command(t_mini *mini, t_token *token)
{
	int	i;

	write(STDOUT_FILENO, "exit\n", 6);
	if (token->cmd[1])
	{
		i = 0;
		while (token->cmd[1][i])
		{
			if (ft_isalpha(token->cmd[1][i++]))
			{
				printf("minishell: exit: %s: numeric argument required\n",
					token->cmd[1]);
				g_status = 2;
				error(mini, '!');
			}
		}
	}
	if (token->cmd[1] && token->cmd[2])
	{
		g_status = 256;
		return ((void)printf("minishell: exit: too many arguments\n"));
	}
	else if (token->cmd[1])
		g_status = ft_atoi(token->cmd[1]) % 256;
	error(mini, '!');
}
