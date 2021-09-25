/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:13:34 by mavinici          #+#    #+#             */
/*   Updated: 2021/09/24 22:27:13 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char *command)
{
	char	path[2021];
	int		len;

	len = ft_strlen(command);
	if (len > 3)
		if (ft_strncmp(command, "pwd ", 4))
			return (not_found(command));
	getcwd(path, 2021);
	printf("%s\n", path);
	return (0);
}
