/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:31:38 by mavinici          #+#    #+#             */
/*   Updated: 2021/11/15 14:31:38 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_standart_fd(t_shell *shell, int fd_in)
{
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

char	*find_command(char *path, char **command)
{
	struct stat	buff;
	char		*new_path;
	char		*new_cmd;

	new_path = ft_strjoin(path, "/");
	new_cmd = ft_strjoin(new_path, *command);
	free(new_path);
	if (stat(new_cmd, &buff) != 0)
	{
		free(new_cmd);
		new_cmd = NULL;
	}
	return (new_cmd);
}

char	*check_path_command(char **str, t_shell *shell)
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

int	ft_check_path(char **str, t_shell *shell)
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
