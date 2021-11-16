/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 04:00:23 by coder             #+#    #+#             */
/*   Updated: 2021/11/15 20:49:32 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	aux_exec(t_shell *shell, char **envp, int fd)
{
	if (fd > 2 && shell->s_redic->redic == -1)
		dup2(fd, 1);
	else if (shell->s_redic->redic == 3 || shell->s_redic->redic == 4)
		dup2(fd, 0);
	check_standart_fd(shell, shell->fd_in);
	if (execve(shell->split_cmd[0], shell->split_cmd, envp) == -1)
		no_file(shell->split_cmd[0], shell);
	exit(errno);
}

int	ft_exec(t_shell *shell, int fd)
{
	pid_t	pid;
	int		ret;
	char	**envp;

	if (!shell->split_cmd[0])
		return (0);
	if (ft_check_path(shell->split_cmd, shell))
		return (127);
	envp = get_env_var(&shell->lst_env, shell);
	pid = fork();
	if (pid == 0)
		aux_exec(shell, envp, fd);
	waitpid(pid, &ret, 0);
	if (g_sh_status != 130)
		g_sh_status = WEXITSTATUS(ret);
	if (envp)
		free_list_string(envp);
	return (g_sh_status);
}
