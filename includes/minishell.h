/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:45:30 by mavinici          #+#    #+#             */
/*   Updated: 2021/09/26 15:07:31 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../42libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_shell
{
	char *command;
}			t_shell;

//builtins
int		ft_pwd(char *command);
void	ft_echo(char *command);
void	ft_env(char *command, char **envi);
int		ft_cd(t_shell *shell);
void	ft_export(char *command, char** env);

//errors
int		not_found(char *command);
int		error_cd(char *path);

//utils
void	free_list_string(char **str);

#endif
