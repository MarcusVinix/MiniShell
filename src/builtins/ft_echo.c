/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:29:44 by jestevam          #+#    #+#             */
/*   Updated: 2021/10/05 20:41:48 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_msg(char *msg, t_list *lst)
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
			printf("%c", msg[count]);
		count++;
	}
	if (msg[count])
	{
		if (!msg[count + 1])
			printf("$");
		sub = ft_substr(msg, ++count, ft_strlen(msg));
		var = find_value(&lst, sub);
		free(sub);
		if (var)
			printf("%s", var);
	}
	printf(" ");
}

void	ft_echo(t_shell *sh)
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
			print_msg(sh->split_cmd[count], sh->lst_env);
		count++;
	}
	if (!flag)
		printf("\n");
	else
		printf("\b");
}