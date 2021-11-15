/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mavinici <mavinici@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:40:08 by mavinici          #+#    #+#             */
/*   Updated: 2021/11/15 14:40:08 by mavinici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	init_struct_redic(t_shell *shell)
{
	shell->s_redic = malloc(sizeof(t_redic));
	shell->s_redic->in = 0;
	shell->s_redic->out = 1;
	shell->s_redic->delimiter = NULL;
	shell->s_redic->file = NULL;
	shell->s_redic->redic = -1;
	shell->s_redic->parse = NULL;
	shell->s_redic->cmd = NULL;
	shell->s_redic->status = malloc(sizeof(t_status));
	shell->s_redic->status->pos = 0;
	shell->s_redic->status->len = 0;
}

void	start_struct(t_shell *shell, char **env)
{
	shell->command = NULL;
	shell->parse_cmd = NULL;
	shell->fd_in = 0;
	shell->fd_out = 1;
	shell->len_env = 0;
	shell->lst_env = create_bckup_env(env, shell);
	shell->status_pipe = malloc(sizeof(t_status));
	shell->status_pipe->len = 0;
	shell->status_pipe->pos = 0;
	shell->in = dup(0);
	shell->ret = 0;
	init_struct_redic(shell);
}

void	reset_struct(t_shell *shell)
{
	if (shell->s_redic->delimiter != NULL)
		free(shell->s_redic->delimiter);
	if (shell->s_redic->file)
		free(shell->s_redic->file);
	if (shell->s_redic->parse)
		free(shell->s_redic->parse);
	if (shell->s_redic->cmd)
		free(shell->s_redic->cmd);
	if (shell->s_redic->status)
		free(shell->s_redic->status);
	if (shell->s_redic)
		free(shell->s_redic);
	init_struct_redic(shell);
}
