/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 22:24:49 by mavinici          #+#    #+#             */
/*   Updated: 2021/10/06 21:59:32 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_found(char *command)
{
	printf("%s: command not found\n", command);
	return (127);
}

void invalid_option(char c)
{
	printf("bash: export: `%c': not a valid option\n", c);
}

void invalid_identifier(char *str)
{
	printf("bash: export: `%s': not a valid identifier\n", str);
}

int	error_no_file(char *path)
{
	printf("minishell: cd: %s: %s\n", path, NO_FILE);
	return (0);
}

int	error_cd(char *message)
{
	printf("minishell: cd: %s\n", message);
	return (0);
}
