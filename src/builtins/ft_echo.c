/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 18:29:44 by jestevam          #+#    #+#             */
/*   Updated: 2021/09/26 15:07:05 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(char *command)
{
	char **str;
	int count;
	int flag;

	flag = 0;
	count = 1;
	str = ft_split(command, ' ');
	if (ft_strcmp(str[0], "echo"))
	{
		printf("%s: command not found\n", command);
		return;
	}
	while (str[count])
	{
		if (!ft_strcmp(str[count], "-n") && count == 1)
			flag = 1;
		else
			printf("%s ", str[count]);
		count++;
	}
	if (!flag)
		printf("\n");
	else
		printf("\b");
	free_list_string(str);
}