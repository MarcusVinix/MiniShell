/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 01:38:52 by coder             #+#    #+#             */
/*   Updated: 2021/10/25 22:53:42 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sigint_handle(int sig_num)
{
	(void)sig_num;
	printf("\n");
	rl_clear_history();
	rl_replace_line(" ", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handle(int sig)
{
	(void)sig;
	printf("OII\n");
	rl_clear_history();
	exit(0);
}