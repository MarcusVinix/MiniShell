/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:13:34 by mavinici          #+#    #+#             */
/*   Updated: 2021/10/24 23:06:11 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int fd)
{
	char	path[2021];

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
