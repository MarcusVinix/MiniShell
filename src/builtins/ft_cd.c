/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 21:15:38 by mavinici          #+#    #+#             */
/*   Updated: 2021/10/25 21:40:02 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static	char	*get_variable(char *path, t_shell *shell, int quotes)
{
	char	*tmp;

	if (quotes == 1)
		return (path);
	tmp = find_value(&shell->lst_env, path + 1);
	free(path);
	if (!tmp || ft_strcmp(tmp, "") == 0)
		tmp = find_value(&shell->lst_env, "HOME");
	return (tmp);
}

static	int	go_to_path(t_shell *shell, char *go_to, int quotes)
{
	char	cwd[2021];
	char	new_cwd[2021];
	int		check;
	int		stat;

	stat = 0;
	check = 0;
	if (*go_to == '$' && (*(go_to + 1) != ' ' || *(go_to + 1) != '\0'))
		go_to = get_variable(go_to, shell, quotes);
	getcwd(cwd, 2021);
	if (chdir(go_to) != 0)
		stat = error_no_file(go_to);
	else
	{
		change_value(&shell->lst_env, "OLDPWD", cwd, 1);
		getcwd(new_cwd, 2021);
		change_value(&shell->lst_env, "PWD", new_cwd,1);
	}
	return (stat);
}

static	int go_to_home(t_shell *shell)
{
	char	*path;
	int		stat;

	stat = 0;
	path = ft_strdup(find_value(&shell->lst_env, "HOME"));
	if (!path)
		return (error_cd("no home"));
	stat = go_to_path(shell, path, 0);
	free(path);
	return (stat);
}

static int	go_to_old_path(t_shell *shell)
{
	char	*old;

	old = find_value(&shell->lst_env, "OLDPWD");
	printf("%s\n", old);
	return (go_to_path(shell, old, 0));
}

int	ft_cd(t_shell *shell, int fd)
{
	int		len;
	int		stat;
	int		quotes;

	stat = 0;
	quotes = 0;
	len = ft_strlen_split(shell->split_cmd);
	if (len > 2)
		return (error_cd("too many arguments"));
	if (fd > 2)
		return (0);
	quotes = check_quotes(shell);
	if (len == 1 || ft_strcmp(shell->split_cmd[1], "~") == 0)
		stat = go_to_home(shell);
	else if (ft_strcmp(shell->split_cmd[1], "-") == 0)
	{
		if (!find_value(&shell->lst_env, "OLDPWD"))
			return (error_cd(NO_OLDPWD));
		stat = go_to_old_path(shell);
	}
	else
		stat = go_to_path(shell, shell->split_cmd[1], quotes);
	return (stat);
}
