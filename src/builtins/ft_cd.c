/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 21:15:38 by mavinici          #+#    #+#             */
/*   Updated: 2021/09/24 23:22:27 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_shell *shell)
{
	char	*path;
	char	cwd[2021];

	path = ft_strchr(shell->command, ' ');
	if (chdir(path + 1) != 0)
	{
		return (error_cd(path));
	}
	shell->command = getcwd(cwd, 2021);
	return (0);
}
