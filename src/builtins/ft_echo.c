/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:29:44 by jestevam          #+#    #+#             */
/*   Updated: 2021/10/21 22:33:06 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_msg(char *msg, t_shell *sh, int fd)
{
	char *var;
	char *sub;
	int count;

	count = 0;
	while (msg[count])
	{
		if (msg[count] == '$')
			break;
		else
			ft_putchar_fd(msg[count], fd);
		count++;
	}
	if (msg[count])
	{
		if (!msg[count + 1])
			ft_putchar_fd('$', fd);
		else if (msg[count + 1] == '?')
			ft_putnbr_fd(*sh->p_status, fd);
		sub = ft_substr(msg, ++count, ft_strlen(msg));
		var = find_value(&sh->lst_env, sub);
		free(sub);
		if (var)
			ft_putstr_fd(var, fd);
	}
	ft_putchar_fd(' ', fd);	
}

void	ft_echo(t_shell *sh, int fd)
{
	int count;
	int flag;

	flag = 0;
	count = 1;
	while (sh->split_cmd[count])
	{
		if (!ft_strcmp(sh->split_cmd[count], "-n") && count == 1)
			flag = 1;
		else
			print_msg(sh->split_cmd[count], sh, fd);
		count++;
	}
	if (!flag)
		ft_putchar_fd('\n', fd);
	else
		ft_putchar_fd('\b', fd);
}