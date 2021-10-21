/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:13:34 by mavinici          #+#    #+#             */
/*   Updated: 2021/10/21 18:20:57 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell, char *command, int fd)
{
	int		len;

	len = ft_strlen(command);
	//if (len > 3)
	//	if (ft_strncmp(command, "pwd ", 4))
	//		return (not_found(command));
	ft_putendl_fd(find_value(&shell->lst_env, "PWD"), fd);
	return (0);
}
