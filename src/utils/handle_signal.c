/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 01:38:52 by coder             #+#    #+#             */
/*   Updated: 2021/11/24 21:37:36 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


// Do a break line
// Save the status 130
void	sigint_handle_cmd(int sig)
{
	(void)sig;
	printf("\n");
	g_sh_status = 130;
}

void	handle_sigquit(int sig)
{
	(void)sig;
	printf("quit (code dumped)\n");
	g_sh_status = 131;
}

// Print a new command line
// Save the status 130
void	sigint_handle(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sh_status = 130;
	}
}

// Do a break line
// Exit the process with status 130
void	handle_heredoc(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	exit(130);
}

// Set up a sigaction handle signal
void	config_sigaction(struct sigaction *act, void (*handler)(int), int sig)
{
	act->sa_handler = handler;
	act->sa_flags = 0;
	sigemptyset(&act->sa_mask);
	sigaction(sig, act, NULL);
}
