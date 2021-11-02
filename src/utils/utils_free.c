/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jestevam < jestevam@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 12:07:25 by mavinici          #+#    #+#             */
/*   Updated: 2021/10/28 21:09:17 by jestevam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_shell *shell)
{	
	if (shell->command)
		free(shell->command);
	if (shell->lst_env)
		ft_lstclear(&shell->lst_env, free);
	if (shell->split_cmd)
		free_list_string(shell->split_cmd);
	if (shell->s_redic->file)
		free(shell->s_redic->file);
}

void free_list_string(char **str)
{
	int count;

	count = 0;
	if (!str)
		return ;
	while (str[count])
		free(str[count++]);
	if (str)
		free(str);
}

void	exit_shell(t_shell *shell, int *status)
{
	if (shell->split_cmd)
		if (shell->split_cmd[1])
			*status = all_number(shell->split_cmd[1]);
	
	free_all(shell);
	rl_clear_history();
	printf("TAMO SAINDO VLW!\nVolte Sempre!!\n");
	exit(*status);
}