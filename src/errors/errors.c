/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:24:49 by mavinici          #+#    #+#             */
/*   Updated: 2021/11/17 22:25:47 by mavinici         ###   ########.fr       */
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
		ft_putendl_fd("No such file or diretory", 2);
	return (0);
}

int	not_found(char *command)
{
	printf("%s: command not found\n", command);
	return (127);
}

int	invalid_option(char *s)
{
	if (ft_strlen(s) > 1)
		printf("bash: export: `%c%c': not a valid option\n", s[0], s[1]);
	else
		printf("bash: export: `%c': not a valid option\n", s[0]);
	return (2);
}

void	invalid_identifier(char *str)
{
	printf("bash: export: `%s': not a valid identifier\n", str);
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
