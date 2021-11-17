/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:29:44 by jestevam          #+#    #+#             */
/*   Updated: 2021/11/17 11:51:59 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_shell *sh, int fd)
{
	int	count;
	int	flag;

	flag = 0;
	count = 1;
	if (sh->s_redic->out != 1)
		fd = sh->s_redic->out;
	else if (sh->s_redic->redic > 2)
		fd = 1;
	while (sh->split_cmd[count])
	{
		if (!ft_strcmp(sh->split_cmd[count], "-n") && count == 1)
			flag = 1;
		else
		{
			ft_putstr_fd(sh->split_cmd[count], fd);
			ft_putchar_fd(' ', fd);
		}
		count++;
	}
	ft_putchar_fd('\b', fd);
	if (!flag)
		ft_putchar_fd('\n', fd);
}
