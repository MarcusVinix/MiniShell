/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:07:25 by mavinici          #+#    #+#             */
/*   Updated: 2021/09/28 21:34:42 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_shell *shell)
{
	free(shell->command);
	free(shell->path.pwd);
	free(shell->path.old_pwd);
}

void free_list_string(char **str)
{
	int count;

	count = 0;
	while (str[count])
		free(str[count++]);
	free(str);
}
