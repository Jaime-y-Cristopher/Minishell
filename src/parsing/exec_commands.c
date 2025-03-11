/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:30:27 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/16 16:27:52 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_commands(t_mini *mini)
{
	int		i;
	t_token	*token;

	token = *mini->commands;
	command_setup(mini);
	mini->pipes = malloc((mini->pipes_i + 1) * sizeof(int *));
	if (!mini->pipes)
		return ;
	i = 0;
	while (i < mini->pipes_i)
	{
		mini->pipes[i] = malloc(sizeof(int) * 2);
		if (!mini->pipes[i])
			return (ft_freeiarr(mini->pipes, i));
		i++;
	}
	mini->pipes[i] = NULL;
	reset_fds(mini, 0);
	mini->pids = malloc((mini->cmd_count + 1) * sizeof(pid_t));
	if (!mini->pids)
		return (ft_freeiarr(mini->pipes, i));
	execute_pipes(mini, token);
	exit_codes();
	close_or_free_pipes(mini, 1);
}

void	execute_pipes(t_mini *mini, t_token *token)
{
	int		i;

	i = 0;
	if (!token->next && mini->cmd_count == 1 && token->is_builtin)
		return (single_command(mini, token));
	while (i < mini->pipes_i)
	{
		if (pipe(mini->pipes[i]) == -1)
			return (perror("Pipe Error"), exit(EXIT_FAILURE));
		i++;
	}
	fork_commands(mini, token);
	close_or_free_pipes(mini, 0);
	i = 0;
	while (i < mini->cmd_count)
	{
		waitpid(mini->pids[i], &g_status, 0);
		i++;
	}
	signal(SIGINT, &handle_sigint);
}

void	fork_commands(t_mini *mini, t_token *token)
{
	mini->i = 0;
	while (token)
	{
		set_redirections(mini, token);
		mini->pids[mini->i] = fork();
		if (mini->pids[mini->i] == -1)
			return (exit(EXIT_FAILURE), perror("Fork Error"));
		if (mini->pids[mini->i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			child_processing(mini, token);
			execve_commands(mini, token);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			reset_fds(mini, 1);
		}
		token = token->next;
		mini->i++;
	}
}

void	child_processing(t_mini *mini, t_token *token)
{
	if (token->input_redir)
	{
		if (dup2(mini->infile, STDIN_FILENO) == -1)
			return (perror("dup2 input error"), exit(EXIT_FAILURE));
		close(mini->infile);
	}
	else if (mini->i > 0)
	{
		if (dup2(mini->pipes[mini->i - 1][0], STDIN_FILENO) == -1)
			return (perror("dup2 input error"), exit(EXIT_FAILURE));
		close(mini->pipes[mini->i - 1][0]);
	}
	if (token->output_redir)
	{
		if (dup2(mini->outfile, STDOUT_FILENO) == -1)
			return (perror("dup2 output error"), exit(EXIT_FAILURE));
		close(mini->outfile);
	}
	else if (mini->i < mini->cmd_count - 1)
	{
		if (dup2(mini->pipes[mini->i][1], STDOUT_FILENO) == -1)
			return (perror("dup2 output error"), exit(EXIT_FAILURE));
		close(mini->pipes[mini->i][1]);
	}
}

void	execve_commands(t_mini *mini, t_token *token)
{
	if (token->is_builtin)
	{
		builtin_commands(mini, token);
		exit(g_status);
	}
	else if (!token->is_builtin && token->cmd)
	{
		if (execve(token->path, token->cmd, mini->env) == -1)
		{
			write(2, token->cmd[0], ft_strlen(token->cmd[0]));
			write(2, ": command not found.\n", 22);
			g_status = 127;
			exit(g_status);
		}
	}
	else
		exit(g_status);
}
