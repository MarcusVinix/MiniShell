/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:45:30 by mavinici          #+#    #+#             */
/*   Updated: 2021/09/29 23:28:58 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "../42libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

# define NO_FILE "No such file or directory"
# define NO_OLDPWD "OLDPWD not set"

typedef struct s_path
{
	char	*pwd;
	char	*old_pwd;
}			t_path;
typedef struct s_shell
{
	char	*command;
	t_path	path;
	t_list	*lst_env;
}			t_shell;

//builtins
int		ft_pwd(char *command);
void	ft_echo(char *command);
void	ft_env(char *command, char **envi);
int		ft_cd(t_shell *shell);
void	ft_export(char *command, char** env);

//errors
int		not_found(char *command);
int		error_cd(char *message);
int		error_no_file(char *path);

//free
void	free_all(t_shell *shell);
void	free_list_string(char **str);

//utils
t_list	*create_bckup_env(char **env);
char	*find_value(t_list **lst, char *key);

#endif
