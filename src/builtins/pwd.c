/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:13:34 by mavinici          #+#    #+#             */
/*   Updated: 2021/09/30 10:51:55 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *shell, char *command)
{
	int		len;

	len = ft_strlen(command);
	if (len > 3)
		if (ft_strncmp(command, "pwd ", 4))
			return (not_found(command));
	printf("%s\n", find_value(&shell->lst_env, "PWD"));
	return (0);
}
