/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 21:15:38 by mavinici          #+#    #+#             */
/*   Updated: 2021/09/27 23:27:08 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	go_to_path(t_shell *shell, char *path)
{
	char	cwd[2021];

	getcwd(cwd, 2021);
	if (chdir(path) != 0)
	{
		error_no_file(path);
	}
	else
	{
		if (shell->path.old_pwd)
		{
			printf("frre?\n");
			free(shell->path.old_pwd);
		}
		shell->path.old_pwd = ft_strdup(cwd);
	}
}

int go_to_home(t_shell *shell)
{
	char	*path;

	path = ft_strdup(getenv("HOME"));
	if (!path)
		return (error_cd("no home"));
	go_to_path(shell, path);
	free(path);
	printf("deu free?\n");
	return (0);
}

void	go_to_old_path(t_shell *shell)
{
	char	cwd[2021];
	char	*path;

	printf("%s\n", shell->path.old_pwd);
	getcwd(cwd, 2021);
	path = ft_strdup(shell->path.old_pwd);
	free(shell->path.old_pwd);
	shell->path.old_pwd = ft_strdup(cwd);
	go_to_path(shell, path);
	free(path);
}

int	ft_cd(t_shell *shell)
{
	int		len;

	len = ft_strlen(shell->command);
	if (len > 2)
		if (ft_strncmp(shell->command, "cd ", 3) != 0)
			return (not_found(shell->command));
	if (((len >= 2 && len <= 4) && ft_strcmp(shell->command + 3, "~") == 0)
		|| len == 2)
		go_to_home(shell);
	else if (ft_strcmp(shell->command + 3, "-") == 0)
	{
		if (!shell->path.old_pwd)
			return (error_cd(NO_OLDPWD));
		go_to_old_path(shell);
	}
	else
		go_to_path(shell, shell->command + 3);
	return (0);
}
