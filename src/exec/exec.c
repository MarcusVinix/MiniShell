/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 04:00:23 by coder             #+#    #+#             */
/*   Updated: 2021/10/19 20:44:04 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*ft_check_path(char *str)
{
	char	*path;
	
	if (ft_strncmp(str, "/bin/", 5) != 0)
		path = ft_strjoin("/bin/", str);
	else
		path = ft_strdup(str);
	return (path);
}

int	ft_exec(t_shell *shell)
{
	pid_t	pid;
	char	*path;
	int		ret;

	path = ft_check_path(shell->split_cmd[0]);
	ret = 0;
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, shell->split_cmd, (char *const *)shell->lst_env) == -1)
			ret = not_found(shell->split_cmd[0]);
		exit(ret);
	}
	wait(&pid);
	free(path);
	return (ret);
}
