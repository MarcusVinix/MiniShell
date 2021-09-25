/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:45:30 by mavinici          #+#    #+#             */
/*   Updated: 2021/09/24 22:32:02 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../42libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

//builtins
int		ft_pwd(char *command);
void	ft_echo(char *command);
void	ft_env(char *command, char **envi);
int		ft_cd(char *command);

//errors
int		not_found(char *command);

#endif
