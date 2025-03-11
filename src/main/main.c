/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:43:39 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/22 15:38:39 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

int	main(int argc, char **argv, char **env)
{
	t_mini	mini;
	char	*env_name;

	if (argc != 1)
		return (1);
	(void)argv;
	init_struct(&mini, env);
	while (1)
	{
		env_name = join_env_name(&mini);
		mini.input = readline(env_name);
		if (!mini.input)
		{
			write(1, "exit\n", 6);
			break ;
		}
		if (*mini.input)
			add_history(mini.input);
		if (main_commands(&mini))
			continue ;
		execute_commands(&mini);
		free_main(&mini);
	}
	error(&mini, '0');
	return (0);
}

int	main_commands(t_mini *mini)
{
	if (mini->input[0] == '\0')
	{
		free(mini->input);
		return (1);
	}
	process_commands(mini);
	if (tokenize_commands(mini, mini->mini_cmds, NULL))
	{
		free_main(mini);
		return (1);
	}
	if (check_quotation(mini))
	{
		free_main(mini);
		return (1);
	}
	return (0);
}
