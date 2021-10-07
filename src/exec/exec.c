/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 04:00:23 by coder             #+#    #+#             */
/*   Updated: 2021/10/08 01:11:20 by coder            ###   ########.fr       */
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

int	ft_exec(t_shell *shell)
{
	pid_t	pid;
	
	signal(SIGQUIT, &sigquit_handle);
	signal(SIGINT, &sigquit_handle);
	pid = fork();
	if (pid == 0)
	{
		if (execve(shell->split_cmd[0], shell->split_cmd, (char *const *)shell->lst_env) == -1)
			return(not_found(shell->split_cmd[0]));
	}
	wait(&pid);
	return (0);
}
