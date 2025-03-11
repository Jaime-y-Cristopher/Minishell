/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:02:40 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/16 15:39:34 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_redirections(t_mini *mini, t_token *token)
{
	if (token->input_redir && !ft_strcmp(token->input_redir, "<"))
	{
		mini->infile = open(token->input_file, O_RDONLY);
		if (mini->infile == -1)
		{
			perror(token->input_file);
			g_status = 1;
			if (!token->access)
				exit(g_status);
			token->access = 0;
		}
	}
	else if (token->input_redir && !ft_strcmp(token->input_redir, "<<"))
	{
		mini->infile = here_doc(mini, token);
		if (mini->infile == -1)
		{
			perror(token->input_file);
			g_status = 1;
			if (!token->access)
				exit(g_status);
			token->access = 0;
		}
	}
	set_redirections2(mini, token);
}

void	set_redirections2(t_mini *mini, t_token *token)
{
	if (token->output_redir && !ft_strcmp(token->output_redir, ">"))
	{
		mini->outfile = open(token->output_file, 01 | 0100 | 01000, 0644);
		if (mini->outfile == -1)
		{
			perror(token->output_file);
			g_status = 1;
			if (!token->access)
				exit(g_status);
			token->access = 0;
		}
	}
	else if (token->output_redir && !ft_strcmp(token->output_redir, ">>"))
	{
		mini->outfile = open(token->output_file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (mini->outfile == -1)
		{
			perror(token->output_file);
			g_status = 1;
			if (!token->access)
				exit(g_status);
			token->access = 0;
		}
	}
}

int	here_doc(t_mini *mini, t_token *token)
{
	char	*line;
	int		fd[2];

	if (pipe(fd) == -1)
		return (perror("Pipe Error\n"), -1);
	token->delimeter = ft_strdelcharf(token->delimeter, "\"\'");
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, token->delimeter, ft_strlen(token->delimeter))
			&& line[ft_strlen(token->delimeter)] == '\n')
		{
			free(line);
			break ;
		}
		if (line && ft_strchr(line, '$'))
			line = expand_variable(mini, line);
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	return (fd[0]);
}

void	close_or_free_pipes(t_mini *mini, int mod)
{
	int		i;

	if (mod == 0)
	{
		if (mini->infile != -1)
			close(mini->infile);
		if (mini->outfile != -1)
			close(mini->outfile);
		i = 0;
		while (i < mini->pipes_i && mini->pipes[i] != NULL)
		{
			if (mini->pipes[i][0] != -1)
				close(mini->pipes[i][0]);
			if (mini->pipes[i][1] != -1)
				close(mini->pipes[i][1]);
			i++;
		}
		return ;
	}
	if (mini->pids)
		free(mini->pids);
	if (mini->pipes)
		ft_freeiarr(mini->pipes, mini->pipes_i);
}

void	reset_fds(t_mini *mini, int mod)
{
	int		i;

	if (mod == 0)
	{
		i = 0;
		while (i < mini->pipes_i)
		{
			mini->pipes[i][0] = -1;
			mini->pipes[i][1] = -1;
			i++;
		}
		mini->infile = -1;
		mini->outfile = -1;
		return ;
	}
	if (mini->i > 0)
	{
		close(mini->pipes[mini->i - 1][0]);
		mini->pipes[mini->i - 1][0] = -1;
	}
	if (mini->i < mini->pipes_i)
	{
		close(mini->pipes[mini->i][1]);
		mini->pipes[mini->i][1] = -1;
	}
}
