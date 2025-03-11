/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:49:06 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/22 12:47:14 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_one_path(t_token *token)
{
	if (token->cmd[0][0] == '/')
	{
		if (access(token->cmd[0], X_OK) == 0)
		{
			token->path = ft_strdup(token->cmd[0]);
			return (1);
		}
		return (1);
	}
	else
		return (0);
	return (0);
}

static void	ft_check_free(char **paths, t_token *token)
{
	if (paths)
		ft_freearr(paths);
	if (token->path == NULL)
		token->path = ft_strdup(token->cmd[0]);
}

static int	ft_check_bucle(char *tmp, char *potential_path, t_token *token)
{
	potential_path = ft_strjoin(tmp, token->cmd[0]);
	if (access(potential_path, X_OK) == 0)
	{
		token->path = potential_path;
		free(tmp);
		return (1);
	}
	free(tmp);
	free(potential_path);
	return (0);
}

void	ft_check_path(t_token *token, t_mini *mini)
{
	char	*path_env;
	char	**paths;
	char	*potential_path;
	char	*tmp;
	int		i;

	potential_path = NULL;
	paths = NULL;
	path_env = ft_getenv("PATH", mini->env);
	tmp = NULL;
	if (path_env)
		paths = ft_split(path_env, ':');
	if (paths && ft_check_one_path(token) == 0)
	{
		i = 0;
		while (paths[i] != NULL)
		{
			tmp = ft_strjoin(paths[i], "/");
			if (ft_check_bucle(tmp, potential_path, token) == 1)
				break ;
			i++;
		}
	}
	ft_check_free(paths, token);
}

char	**allocate_new_cmds(t_token *token, char **cmds,
	int *old_len, int *new_len)
{
	while (token->cmd && token->cmd[*old_len])
		(*old_len)++;
	while (cmds[*new_len] && ft_strcmp(cmds[*new_len], "|")
		&& !is_redirect(cmds[*new_len]))
		(*new_len)++;
	return (malloc(sizeof(char *) * (*old_len + *new_len + 1)));
}
