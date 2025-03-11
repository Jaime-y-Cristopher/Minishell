/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:29:04 by ctommasi          #+#    #+#             */
/*   Updated: 2024/12/13 14:12:09 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "history")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "setcolour"));
}

int	is_output_redirect(char *cmd)
{
	return (!ft_strcmp(cmd, ">>") || !ft_strcmp(cmd, ">"));
}

int	is_input_redirect(char *cmd)
{
	return (!ft_strcmp(cmd, "<<") || !ft_strcmp(cmd, "<"));
}

int	is_redirect(char *cmd)
{
	return (is_input_redirect(cmd) || is_output_redirect(cmd));
}

int	is_del(char cmd)
{
	return (cmd == '|' || cmd == '>' || cmd == '<');
}
