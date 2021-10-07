/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 04:00:23 by coder             #+#    #+#             */
/*   Updated: 2021/10/07 05:58:40 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigquit_handle(int sig_num)
{
	(void)sig_num;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_exec(t_shell *shell)
{
	pid_t	pid;
	
	signal(SIGQUIT, &sigquit_handle);
	signal(SIGINT, &sigquit_handle);
	pid = fork();
	if (pid == 0)
	{
		if (execve(shell->split_cmd[0], shell->split_cmd, (char *const *)shell->lst_env) == -1)
			not_found(shell->split_cmd[0]);
		exit(0);
	}
	wait(&pid);
}
