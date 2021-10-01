/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:29:44 by jestevam          #+#    #+#             */
/*   Updated: 2021/09/30 22:41:36 by jestevam         ###   ########.fr       */
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
	char **str;
	int count;
	int flag;

	flag = 0;
	count = 1;
	str = ft_split(sh->command, ' ');
	if (ft_strcmp(str[0], "echo"))
	{
		printf("%s: command not found\n", sh->command);
		return;
	}
	while (str[count])
	{
		if (!ft_strcmp(str[count], "-n") && count == 1)
			flag = 1;
		else
			print_msg(str[count], sh->lst_env);
		count++;
	}
	if (!flag)
		printf("\n");
	else
		printf("\b");
	free_list_string(str);
}