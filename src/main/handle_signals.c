/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaimesan <jaimesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:34:47 by ctommasi          #+#    #+#             */
/*   Updated: 2025/01/16 16:24:01 by jaimesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signals(void)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_d;
	struct sigaction	ctrl_quit;

	ft_memset(&ctrl_c, 0, sizeof(ctrl_c));
	ctrl_c.sa_handler = &handle_sigint;
	ctrl_c.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &ctrl_c, NULL) == -1)
		perror("sigaction ctrl + c");
	ft_memset(&ctrl_d, 0, sizeof(ctrl_d));
	ctrl_d.sa_handler = &handle_sigquit;
	ctrl_d.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &ctrl_d, NULL) == -1)
		perror("sigaction ctrl + d");
	ft_memset(&ctrl_quit, 0, sizeof(ctrl_quit));
	ctrl_quit.sa_handler = SIG_IGN;
	ctrl_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &ctrl_quit, NULL) == -1)
		perror("sigaction ctrl + \\");
}

void	handle_sigint(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 130;
}

void	handle_sigquit(int signal)
{
	(void)signal;
	g_status = 131;
}

void	exit_codes(void)
{
	if (WIFEXITED(g_status))
		g_status = WEXITSTATUS(g_status);
	else if (WIFSIGNALED(g_status))
	{
		if (g_status == 130 || g_status == 131)
			g_status = WTERMSIG(g_status);
		else
			g_status = 128 + WTERMSIG(g_status);
	}
	else
		g_status = -1;
}
