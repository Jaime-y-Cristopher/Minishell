/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:57:13 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/22 15:51:25 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_cd(t_mini *mini, char *cwd)
{
	mini->oldpath = NULL;
	mini->oldpath = ft_strdup(cwd);
	if (mini->oldpwd_off == 1)
		save_oldpwd(mini, mini->oldpath);
}

void	cd(t_mini *mini, t_token *token)
{
	char	*path;
	char	*oldpath;
	char	cwd[1024];

	oldpath = NULL;
	mini->oldpwd_off = 1;
	if (getcwd(cwd, sizeof(cwd)))
		oldpath = ft_strdup(cwd);
	save_oldpath(mini, oldpath);
	if (mini->oldpath == NULL)
		mini->oldpath = ft_strdup(cwd);
	free(oldpath);
	path = resolve_cd_path(mini, token);
	if (!path)
	{
		g_status = 1;
		return ;
	}
	if (ft_chdir(path) == 1)
		return ;
	free(path);
	free(mini->oldpath);
	set_cd(mini, cwd);
	g_status = 0;
}

int	ft_chdir(char *path)
{
	if (chdir(path) == -1)
	{
		g_status = 1;
		free(path);
		perror("Error");
		return (1);
	}
	return (0);
}

char	*check_per(t_mini *mini, t_token *token, char *path)
{
	if (!token->cmd[1] || ft_strcmp(token->cmd[1], "~") == 0
		|| !ft_strcmp(token->cmd[1], "--"))
		path = ft_strdup(find_path(mini, "HOME="));
	else if (ft_strncmp(token->cmd[1], "~", 1) == 0 && token->cmd[1][1] != '\0')
		path = ft_strjoin(find_path(mini, "HOME="), token->cmd[1] + 1);
	return (path);
}

void	save_oldpath(t_mini *mini, char *oldpath)
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
		if (ft_strncmp(mini->env[i], "OLDPWD=", 6 + 1) == 0)
			new_env[j++] = ft_strjoin("OLDPWD=", oldpath);
		else
			new_env[j++] = ft_strdup(mini->env[i]);
		i++;
	}
	new_env[j] = NULL;
	ft_freearr(mini->env);
	mini->env = new_env;
}
