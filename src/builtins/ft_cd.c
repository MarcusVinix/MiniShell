/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 21:15:38 by mavinici          #+#    #+#             */
/*   Updated: 2021/10/04 19:23:25 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static	char	*get_variable(char *path, t_shell *shell)
{
	char	*tmp;

	tmp = find_value(&shell->lst_env, path);
	free(path - 1);
	if (!tmp || ft_strcmp(tmp, "") == 0)
		tmp = find_value(&shell->lst_env, "HOME");
	return (tmp);
}

static	void	go_to_path(t_shell *shell, char *go_to)
{
	char	cwd[2021];
	char	new_cwd[2021];
	char	*path;
	int		check;

	check = 0;
	path = ft_strtrim(go_to, " ");
	if (*path == '$' && (*(path + 1) != ' ' || *(path + 1) != '\0'))
	{
		path = get_variable(path + 1, shell);
		check = 1;
	}
	getcwd(cwd, 2021);
	if (chdir(path) != 0)
		error_no_file(path);
	else
	{
		change_value(&shell->lst_env, "OLDPWD", cwd);
		getcwd(new_cwd, 2021);
		change_value(&shell->lst_env, "PWD", new_cwd);
	}
	if (!check)
		free(path);
}

static	int go_to_home(t_shell *shell)
{
	char	*path;

	path = ft_strdup(find_value(&shell->lst_env, "HOME"));
	if (!path)
		return (error_cd("no home"));
	go_to_path(shell, path);
	free(path);
	return (0);
}

static void	go_to_old_path(t_shell *shell)
{
	char	*old;

	old = find_value(&shell->lst_env, "OLDPWD");
	printf("%s\n", old);
	go_to_path(shell, old);
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
	else if (is_all_space(shell->command + 2))
		go_to_home(shell);
	else if (ft_strcmp(shell->command + 3, "-") == 0)
	{
		if (!find_value(&shell->lst_env, "OLDPWD"))
			return (error_cd(NO_OLDPWD));
		go_to_old_path(shell);
	}
	else
		go_to_path(shell, shell->command + 3);
	return (0);
}
