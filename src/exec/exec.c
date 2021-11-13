/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 04:00:23 by coder             #+#    #+#             */
/*   Updated: 2021/11/04 22:09:30 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_standart_fd(t_shell *shell, int fd_in, int fd_out)
{
	(void)fd_out;
	if (fd_in != 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
	if (shell->s_redic->in != 0)
	{
		dup2(shell->s_redic->in, 0);
		close(shell->s_redic->in);
	}
	if (shell->s_redic->out != 1)
	{
		dup2(shell->s_redic->out, 1);
		close(shell->s_redic->out);
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
	
	if(!shell->split_cmd[0])
		return (0);
	if (ft_check_path(shell->split_cmd, shell))
		return (127);
	envp = get_env_var(&shell->lst_env, shell);
	ret = 0;
	config_sigaction(&shell->act, SIG_IGN, SIGINT);
	pid = fork();
	config_sigaction(&shell->act, sigint_handle_cmd, SIGINT);
	if (pid == 0)
	{
		if (fd > 2 && shell->s_redic->redic == -1)
			dup2(fd, 1);
		else if (shell->s_redic->redic == 3 || shell->s_redic->redic == 4)
			dup2(fd, 0);
		check_standart_fd(shell, shell->fd_in, shell->fd_out);
		if (execve(shell->split_cmd[0], shell->split_cmd, envp) == -1)
			ret = no_file(shell->split_cmd[0], shell);
		exit(ret);
	}
	waitpid(pid, &ret, 0);
	if (envp)
		free_list_string(envp);
	if (ret > 256)
		ret = 127;
	return (ret);
}
