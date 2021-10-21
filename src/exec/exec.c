/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 04:00:23 by coder             #+#    #+#             */
/*   Updated: 2021/10/21 19:34:34 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_standart_fd(int fd_in, int fd_out)
{
	if (fd_in != 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
	if (fd_out != 1)
	{
		dup2(fd_in, 1);
		close(fd_out);
	}
}

static	char	*ft_check_path(char *str)
{
	char	*path;
	
	if (ft_strncmp(str, "/bin/", 5) != 0)
		path = ft_strjoin("/bin/", str);
	else
		path = ft_strdup(str);
	return (path);
}

int	ft_exec(t_shell *shell, int fd)
{
	pid_t	pid;
	char	*path;
	int		ret;
	int		status;

	path = ft_check_path(shell->split_cmd[0]);
	ret = 0;
	pid = fork();
	if (pid == 0)
	{
		if (fd > 2)
			dup2(fd, 1);
		check_standart_fd(shell->fd_in, shell->fd_out);
		if (execve(path, shell->split_cmd, (char *const *)shell->lst_env) == -1)
			ret = not_found(shell->split_cmd[0]);
		exit(ret);
	}
	if (pid == -1)
	{
		printf("Minishell: erro ao criar o fork\n");
		ft_putendl_fd(strerror(errno), 2);
		return (-1);
	}
	waitpid(pid, &status, 0);
	free(path);
	return (ret);
}
