/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:13:34 by mavinici          #+#    #+#             */
/*   Updated: 2021/11/03 16:28:38 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int fd, t_shell *shell)
{
	char	path[2021];

	if (shell->s_redic->redic > 2)
		fd = 1;
	if (getcwd(path, 2021))
		ft_putendl_fd(path, fd);
	else
	{
		ft_putendl_fd("minishell: ", 2);
		ft_putendl_fd("pwd: ", 2);
		ft_putendl_fd(strerror(errno), 2);
	}
	return (0);
}
