/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 01:38:52 by coder             #+#    #+#             */
/*   Updated: 2021/11/03 19:16:34 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sigint_handle(int sig_num)
{
	(void)sig_num;
	//printf("justo\n");
	//rl_clear_history();
	//rl_replace_line(" ", 0);
	//rl_on_new_line();
	//rl_redisplay();
}

void	sigquit_handle(int sig)
{
	(void)sig;
	printf("OII\n");
	rl_clear_history();
	exit(0);
}

void	handle_heredoc(int sig_num)
{
	(void)sig_num;
	printf("to aqui\n");
	exit(0);
}
