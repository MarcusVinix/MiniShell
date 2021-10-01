/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:45:30 by mavinici          #+#    #+#             */
/*   Updated: 2021/09/30 20:43:57 by jestevam         ###   ########.fr       */
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

typedef struct s_shell
{
	char	*command;
	t_list	*lst_env;
}			t_shell;

//builtins
int		ft_pwd(t_shell *shell, char *command);
void	ft_echo(char *command);
void	ft_env(char *command, t_shell *sh);
int		ft_cd(t_shell *shell);
void	ft_export(char *command, t_shell *sh);

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
int		change_value(t_list **lst, char *key, char *new_value);


#endif
