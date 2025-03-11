/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:22:34 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/16 15:40:22 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_commands(t_mini *mini, t_token *token)
{
	if (!ft_strcmp(token->cmd[0], "history"))
		print_history();
	else if (!ft_strcmp(token->cmd[0], "env"))
		print_env(mini);
	else if (!ft_strcmp(token->cmd[0], "echo"))
		echo(token);
	else if (!ft_strcmp(token->cmd[0], "pwd"))
		print_pwd(mini);
	else if (!ft_strcmp(token->cmd[0], "cd"))
		cd(mini, token);
	else if (!ft_strcmp(token->cmd[0], "export"))
		export(mini, token);
	else if (!ft_strcmp(token->cmd[0], "unset"))
		unset(token, mini);
	else if (!ft_strcmp(token->cmd[0], "exit"))
		exit_command(mini, token);
	else if (!ft_strcmp(token->cmd[0], "setcolour"))
		set_colour(mini, token);
}

void	single_command(t_mini *mini, t_token *token)
{
	token->access = 1;
	set_redirections(mini, token);
	if (!token->access)
		return ;
	if (mini->infile != -1)
	{
		if (dup2(mini->infile, STDIN_FILENO) == -1)
			return (exit(EXIT_FAILURE), perror("dup2 input error"));
	}
	if (mini->outfile != -1)
	{
		if (dup2(mini->outfile, STDOUT_FILENO) == -1)
			return (exit(EXIT_FAILURE), perror("dup2 output error"));
	}
	builtin_commands(mini, token);
	if (mini->infile != STDIN_FILENO)
		dup2(mini->original_stdin, STDIN_FILENO);
	if (mini->outfile != STDOUT_FILENO)
		dup2(mini->original_stdout, STDOUT_FILENO);
}

void	command_setup(t_mini *mini)
{
	t_token	*token;
	int		count;

	token = *mini->commands;
	count = 0;
	while (token)
	{
		count++;
		token = token->next;
	}
	mini->cmd_count = count;
	mini->pipes_i = 0;
	if (count != 0)
		mini->pipes_i = count - 1;
	mini->pids = NULL;
	mini->pipes = NULL;
}

t_token	*ft_newtoken(t_token *token)
{
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->cmd = NULL;
	token->path = NULL;
	token->input_redir = NULL;
	token->output_redir = NULL;
	token->input_file = NULL;
	token->output_file = NULL;
	token->delimeter = NULL;
	token->pipe = NULL;
	token->is_builtin = 0;
	token->complete = 0;
	token->newline = 0;
	token->expansion = 0;
	token->access = 0;
	token->next = NULL;
	return (token);
}

void	ft_tokenadd_back(t_mini *mini, t_token *token)
{
	t_token	*last;

	if (!mini->commands || !token)
		return ;
	if (!*mini->commands)
	{
		*mini->commands = token;
		return ;
	}
	last = *mini->commands;
	while (last->next)
		last = last->next;
	last->next = token;
}
