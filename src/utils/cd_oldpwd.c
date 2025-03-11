/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_oldpwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 15:45:36 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/22 15:46:07 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*replace_or_copy(char *env_var, char *oldpath, int *found)
{
	if (ft_strncmp(env_var, "OLDPWD=", 7) == 0)
	{
		*found = 1;
		return (ft_strjoin("OLDPWD=", oldpath));
	}
	return (ft_strdup(env_var));
}

static char	**create_new_env(char **env, char *oldpath, int *found, int len)
{
	char	**new_env;
	int		i;

	new_env = malloc((len + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_env[i] = replace_or_copy(env[i], oldpath, found);
		if (!new_env[i])
			return (ft_freearr(new_env), NULL);
		i++;
	}
	if (!*found)
		new_env[i++] = ft_strjoin("OLDPWD=", oldpath);
	new_env[i] = NULL;
	return (new_env);
}

void	save_oldpwd(t_mini *mini, char *oldpath)
{
	int		found;
	int		len;
	char	**new_env;

	len = ft_arrlen(mini->env);
	found = 0;
	new_env = create_new_env(mini->env, oldpath, &found, len);
	if (!new_env)
		error(mini, 'M');
	ft_freearr(mini->env);
	mini->env = new_env;
}
