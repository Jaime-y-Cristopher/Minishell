/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctommasi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 13:15:59 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/16 13:16:01 by ctommasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_variable(t_mini *mini, char *str)
{
	char	*res;
	char	*var_name;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (!str)
		return (str);
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			var_name = extract_var_name(str, &i);
			res = add_var_value(mini, res, var_name);
			continue ;
		}
		else
			res = process_regular_char(res, str[i], &k);
		i++;
	}
	return (free(str), res);
}

char	*extract_var_name(char *str, int *i)
{
	char	*var_name;
	int		j;

	var_name = ft_strdup("");
	if (!var_name)
		return (str);
	j = 0;
	while (str[*i] && str[*i] != ' ' && str[*i] != '$'
		&& str[*i] != '\t' && str[*i] != '\n')
	{
		var_name = ft_realloc(var_name,
				ft_strlen(var_name), ft_strlen(var_name) + 2);
		var_name[j] = str[*i];
		var_name[j + 1] = '\0';
		j++;
		(*i)++;
	}
	return (var_name);
}

char	*add_var_value(t_mini *mini, char *res, char *var_name)
{
	char	*var_value;
	char	*temp;

	var_value = get_var_value(mini, var_name);
	if (!var_value)
	{
		if (!ft_strncmp(var_name, "?", 1))
		{
			free(res);
			res = ft_itoa(g_status);
		}
		free(var_name);
		return (res);
	}
	temp = ft_strjoin(res, var_value);
	free(res);
	res = temp;
	free(var_name);
	return (res);
}

char	*process_regular_char(char *res, char current_char, int *k)
{
	int	len;

	len = ft_strlen(res);
	res = ft_realloc(res, len, len + 2);
	res[len] = current_char;
	res[len + 1] = '\0';
	(*k) += 2;
	return (res);
}

char	*get_var_value(t_mini *mini, char *var_name)
{
	int		i;
	int		arr_len;
	char	*value;

	arr_len = ft_arrlen(mini->env);
	i = 0;
	while (i < arr_len)
	{
		if (ft_strncmp(mini->env[i], var_name, ft_strlen(var_name)) == 0
			&& mini->env[i][ft_strlen(var_name)] == '=')
		{
			value = ft_strchr(mini->env[i], '=');
			value++;
			return (value);
		}
		i++;
	}
	return (NULL);
}
