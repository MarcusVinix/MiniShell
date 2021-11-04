/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 01:38:52 by coder             #+#    #+#             */
/*   Updated: 2021/11/03 22:08:53 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


void	sigquit_handle(int sig)
{
	(void)sig;
	printf("OII\n");
	rl_clear_history();
	exit(0);
}

void	sigint_handle(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_clear_history();
	rl_replace_line(" ", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_heredoc(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	exit(0);
}

void	config_sigaction(struct sigaction *act, void (*handle)(int), int sig)
{
	act->sa_handler = handle;
	act->sa_flags = 0;
	sigemptyset(&act->sa_mask);
	sigaction(sig, act, NULL);
}