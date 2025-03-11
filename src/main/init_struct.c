/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:59:33 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/23 15:03:51 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_mini *mini, char **env)
{
	mini->pids = NULL;
	mini->pipes = NULL;
	mini->input = NULL;
	mini->mini_cmds = NULL;
	mini->env = NULL;
	mini->log_name = NULL;
	mini->sesion_name = NULL;
	mini->full_name = NULL;
	mini->path = NULL;
	mini->env_name = NULL;
	mini->oldpath = NULL;
	mini->full_path = NULL;
	mini->quote_types = NULL;
	mini->commands = malloc(sizeof(t_token *));
	if (!mini->commands)
		return ;
	*mini->commands = NULL;
	dup_env(mini, env);
	setup_signals();
	mini->name_clr = ft_strdup("\033[1;38;5;214m");
	mini->pwd_clr = ft_strdup("\033[1;38;5;5m");
	get_env_name(mini);
	mini->original_stdin = dup(STDIN_FILENO);
	mini->original_stdout = dup(STDOUT_FILENO);
	save_shlvl(mini);
}

void	init_quotes(t_quote *q)
{
	q->double_quote = 0;
	q->single_quote = 0;
	q->escape = 0;
	q->expansion = 0;
	q->print = 0;
}
