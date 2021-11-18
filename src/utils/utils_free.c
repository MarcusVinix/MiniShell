/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:07:25 by mavinici          #+#    #+#             */
/*   Updated: 2021/11/17 22:43:44 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_shell *shell)
{	
	if (shell->command)
		free(shell->command);
	if (shell->lst_env)
		ft_lstclear(&shell->lst_env, free);
	if (shell->status_pipe)
		free(shell->status_pipe);
	if (shell->s_redic->file)
		free(shell->s_redic->file);
}

void	free_list_string(char **str)
{
	int	count;

	count = 0;
	if (!str)
		return ;
	while (str[count])
		free(str[count++]);
	if (str)
		free(str);
}

void	exit_shell(t_shell *shell)
{
	free_all(shell);
	rl_clear_history();
	exit(g_sh_status);
}

void	free_four(char *var1, char *var2, char *var3, char *var4)
{
	free(var1);
	free(var2);
	free(var3);
	free(var4);
}
