/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 04:00:23 by coder             #+#    #+#             */
/*   Updated: 2021/10/24 22:26:06 by mavinici         ###   ########.fr       */
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

static char	*find_command(char *path, char **command)
{
	struct stat	buff;
	char		*new_path;
	char		*new_cmd;

	new_path = ft_strjoin(path, "/");
	new_cmd = ft_strjoin(new_path, *command);
	free(new_path);
	if (stat(new_cmd, &buff) != 0 )
	{
		free(new_cmd);
		new_cmd = NULL;
	}
	return (new_cmd);
}

static char	*check_path_command(char **str, t_shell *shell)
{
	char	*path;
	char	**split_path;
	char	*command;
	int		i;

	path = find_value(&shell->lst_env, "PATH");
	if (!path)
		return (NULL);
	split_path = ft_split(path, ':');
	i = 0;
	while (split_path[i])
	{
		command = find_command(split_path[i], str);
		if (command)
			break ;
		i++;
	}
	free_list_string(split_path);
	return (command);
}

static int	ft_check_path(char **str, t_shell *shell)
{
	char	*path;
	
	if (!(ft_strchr(str[0], '/')))
	{
		path = check_path_command(str, shell);
		if (!path)
			return (not_found(shell->split_cmd[0]));
		free(str[0]);
		str[0] = path;
	}
	return (0);
}

int	ft_exec(t_shell *shell, int fd)
{
	pid_t	pid;
	int		ret;
	char	**envp;
	
	if (ft_check_path(shell->split_cmd, shell))
		return (127);
	envp = get_env_var(&shell->lst_env, shell);
	ret = 0;
	pid = fork();
	if (pid == 0)
	{
		if (fd > 2)
			dup2(fd, 1);
		check_standart_fd(shell->fd_in, shell->fd_out);
		if (execve(shell->split_cmd[0], shell->split_cmd, envp) == -1)
			return (no_file(shell->split_cmd[0]));
		exit(ret);
	}
	waitpid(pid, &ret, 0);
	if (envp)
		free_list_string(envp);
	return (ret);
}
