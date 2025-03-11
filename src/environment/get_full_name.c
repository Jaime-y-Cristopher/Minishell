/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:57:39 by jaimesan          #+#    #+#             */
/*   Updated: 2025/01/22 15:13:55 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_colour(char *colour, char *p_clr)
{
	char	*temp;

	temp = NULL;
	if (!colour && !p_clr)
		return (printf("Usage:\n\tsetcolour name %s\n",
				"<colour> [pwd <colour>]"), NULL);
	if (!ft_strcmp("gray", colour))
		temp = ft_strdup("\033[1;90m");
	else if (!ft_strcmp("red", colour))
		temp = ft_strdup("\033[1;38;5;1m");
	else if (!ft_strcmp("green", colour))
		temp = ft_strdup("\033[1;38;5;2m");
	else if (!ft_strcmp("orange", colour))
		temp = ft_strdup("\033[1;38;5;214m");
	else if (!ft_strcmp("blue", colour))
		temp = ft_strdup("\033[1;96m");
	else if (!ft_strcmp("magenta", colour))
		temp = ft_strdup("\033[1;38;5;5m");
	else if (!ft_strcmp("yellow", colour))
		temp = ft_strdup("\033[1;93m");
	else if (!ft_strcmp("white", colour))
		temp = ft_strdup("\033[1;38;5;7m");
	else
		return (printf("[setcolour list] for colour list.\n"), p_clr);
	return (free(p_clr), temp);
}

void	set_colour(t_mini *m, t_token *t)
{
	int		i;

	i = 1;
	if (!t->cmd[i])
		return ((void)get_colour(NULL, NULL));
	if (!ft_strcmp("list", t->cmd[i]))
		return ((void)printf("%s %s, %s, %s, %s, %s, %s, %s & %s.\n",
				"Available Colours:\n\t", "gray", "red", "green",
				"orange", "blue", "magenta", "yellow", "white"));
	while (t->cmd[i])
	{
		if (!ft_strcmp("name", t->cmd[i]) && t->cmd[i + 1])
		{
			m->name_clr = get_colour(t->cmd[i + 1], m->name_clr);
			i++;
		}
		else if (!ft_strcmp("pwd", t->cmd[i]) && t->cmd[i + 1])
		{
			m->pwd_clr = get_colour(t->cmd[i + 1], m->pwd_clr);
			i++;
		}
		else
			return ((void)get_colour(NULL, NULL));
		i++;
	}
}

void	get_env_name(t_mini *mini)
{
	mini->oldpwd_off = 1;
	mini->log_name = ft_getenv("LOGNAME", mini->env);
	get_session_name(mini);
	mini->log_name = ft_strjoin(mini->log_name, "@");
	mini->full_name = ft_strjoin(mini->log_name, mini->sesion_name);
}

void	get_session_name(t_mini *mini)
{
	int		i;
	char	**split1;
	char	**split2;
	char	**split3;

	i = 0;
	while (mini->env[i])
	{
		split1 = ft_split(mini->env[i], '=');
		if (!split1 || !split1[0])
			return (ft_freearr(split1));
		if (!ft_strcmp(split1[0], "SESSION_MANAGER"))
		{
			split2 = ft_split(split1[1], '/');
			if (!split2 || !split2[1])
				return (ft_freearr(split1), ft_freearr(split2));
			split3 = ft_split(split2[1], '.');
			if (split3 && split3[0])
				mini->sesion_name = ft_strdup(split3[0]);
			return (ft_freearr(split1), ft_freearr(split2), ft_freearr(split3));
		}
		ft_freearr(split1);
		i++;
	}
}

char	*join_env_name(t_mini *mini)
{
	char	cwd[1024];
	char	*join1;
	char	*join2;

	if (mini->env_name != NULL)
		free(mini->env_name);
	join1 = ft_strjoin(mini->name_clr, mini->full_name);
	join2 = ft_strjoin(join1, "\033[0m");
	free(join1);
	join1 = ft_strjoin(join2, ":~");
	free(join2);
	join2 = ft_strjoin(join1, mini->pwd_clr);
	free(join1);
	join1 = ft_strjoin(join2, getcwd(cwd, sizeof(cwd)));
	free(join2);
	join2 = ft_strjoin(join1, "\033[0m");
	free(join1);
	mini->env_name = ft_strjoin(join2, "$ ");
	free(join2);
	return (mini->env_name);
}
