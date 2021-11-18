/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 19:28:24 by mavinici          #+#    #+#             */
/*   Updated: 2021/11/13 19:28:24 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_no_file(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(NO_FILE, 2);
	return (1);
}

int	error_cd(char *message)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putendl_fd(message, 2);
	return (1);
}

int	no_file(char *file, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(" :", 2);
	ft_putendl_fd(strerror(errno), 2);
	if (shell->s_redic->redic)
		g_sh_status = 1;
	return (127);
}

int	error_newline(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
	g_sh_status = 2;
	return (-1);
}

int	ft_invalid_identifier_unset(char *str)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}
