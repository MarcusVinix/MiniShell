/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:24:49 by mavinici          #+#    #+#             */
/*   Updated: 2021/11/23 20:49:11 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	invalid_permission_or_file(char *comm, char *str, int signal)
{
	(void)str;
	ft_putstr_fd(comm, 2);
	ft_putstr_fd(": \"", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\": ", 2);
	if (signal == 1)
		ft_putendl_fd("Permision denied", 2);
	else if (signal == 2)
		ft_putendl_fd(NO_FILE, 2);
	return (0);
}

int	not_found(char *command)
{
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
	return (127);
}

int	invalid_option(char *s)
{
	ft_putstr_fd("bash: export: `", 2);
	if (ft_strlen(s) > 1)
	{
		ft_putchar_fd(s[0], 2);
		ft_putchar_fd(s[1], 2);
	}
	else
		ft_putchar_fd(s[0], 2);
	ft_putendl_fd("': not a valid option", 2);
	return (2);
}

void	invalid_identifier(char *str)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	error_heredoc(char **str, int *i)
{
	ft_putstr_fd("-MiniShell: warning: ", 2);
	ft_putstr_fd("here-document delimited by ", 2);
	ft_putstr_fd("end-of-file (wanted `", 2);
	ft_putstr_fd(str[*i], 2);
	ft_putendl_fd("')", 2);
	if (str[++*i])
		return (0);
	else
		return (1);
}
