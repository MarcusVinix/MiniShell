/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:24:49 by mavinici          #+#    #+#             */
/*   Updated: 2021/11/03 16:58:04 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_found(char *command)
{
	printf("%s: command not found\n", command);
	return (127);
}

int	invalid_option(char *s)
{
	if (ft_strlen(s) > 1)
		printf("bash: export: `%c%c': not a valid option\n", s[0], s[1]);
	else
		printf("bash: export: `%c': not a valid option\n", s[0]);
	return (2);
}

void	invalid_identifier(char *str)
{
	printf("bash: export: `%s': not a valid identifier\n", str);
}
