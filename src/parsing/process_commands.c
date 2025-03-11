/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:40:19 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/22 16:03:24 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_commands(t_mini *mini)
{
	int	count;
	int	i;
	int	j;
	int	k;

	mini->q = NO_QUOTE;
	count = count_commands(mini);
	if (count == 0)
		return ;
	mini->mini_cmds = malloc(sizeof(char *) * (count + 1));
	if (!mini->mini_cmds)
		return (perror("Memory Allocation Failure\n"), exit(EXIT_FAILURE));
	i = 0;
	while (i < count)
	{
		mini->mini_cmds[i] = NULL;
		i++;
	}
	i = 0;
	j = 0;
	k = 0;
	process_commands2(mini, i, j, k);
}

void	process_commands2(t_mini *mini, int i, int j, int k)
{
	char	*cmd;

	cmd = NULL;
	while (mini->input[i])
	{
		if (mini->input[i] == '\\' && mini->input[i + 1] != '\0')
		{
			cmd = append_char_cmd(cmd, mini->input[i], &k);
			cmd = append_char_cmd(cmd, mini->input[i + 1], &k);
			i += 2;
			continue ;
		}
		mini->q = get_quote(mini->q, mini->input[i]);
		if (mini->q != NO_QUOTE || (mini->input[i] != ' '
				&& !is_del(mini->input[i])))
			cmd = append_char_cmd(cmd, mini->input[i], &k);
		if (mini->q == NO_QUOTE && (mini->input[i] == ' '
				|| is_del(mini->input[i])))
			handle_end_cmd(mini->mini_cmds, &cmd, &k, &j);
		if (mini->q == NO_QUOTE && is_del(mini->input[i]))
			handle_redirections(mini, &cmd, &i, &j);
		i++;
	}
	handle_end_cmd(mini->mini_cmds, &cmd, &k, &j);
	mini->mini_cmds[j] = NULL;
}

void	handle_redirections(t_mini *mini, char **cmd, int *i, int *j)
{
	*cmd = ft_realloc(*cmd, 0, 2);
	(*cmd)[0] = mini->input[*i];
	(*cmd)[1] = '\0';
	if (mini->input[*i + 1] && is_del(mini->input[*i + 1]))
	{
		(*i)++;
		*cmd = ft_realloc(*cmd, 1, 3);
		(*cmd)[1] = mini->input[*i];
		(*cmd)[2] = '\0';
	}
	mini->mini_cmds[*j] = ft_strdup(*cmd);
	free(*cmd);
	*cmd = NULL;
	(*j)++;
}

char	*append_char_cmd(char *cmd, char c, int *k)
{
	cmd = ft_realloc(cmd, *k, *k + 2);
	cmd[*k] = c;
	(*k)++;
	cmd[*k] = '\0';
	return (cmd);
}

void	handle_end_cmd(char **cmd_list, char **cmd, int *k, int *j)
{
	if (*k > 0 && *cmd)
	{
		cmd_list[*j] = ft_strdup(*cmd);
		free(*cmd);
		(*j)++;
		*k = 0;
		*cmd = NULL;
	}
}
