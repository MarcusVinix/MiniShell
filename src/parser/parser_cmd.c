
#include <minishell.h>

static void create_split_cmd(t_shell *shell)
{
	if (shell->s_redic->parse)
		shell->split_cmd = ft_split(shell->s_redic->parse, ' ');
	else if (shell->s_redic->cmd)
		shell->split_cmd = ft_split(shell->s_redic->cmd, ' ');
	else if (shell->parse_cmd)
		shell->split_cmd = ft_split(shell->parse_cmd, ' ');
	else
		shell->split_cmd = ft_split(shell->command, ' ');
}

int	check_command(t_shell *shell, int fd)
{
	create_split_cmd(shell);
	config_sigaction(&shell->act, sigint_handle_cmd, SIGINT);
	if (ft_strcmp(shell->split_cmd[0], "echo") == 0)
		ft_echo(shell, fd);
	else if (find_index(shell->split_cmd[0], '=') > 0)
		ft_export(shell, fd, 0);
	else if (ft_strcmp(shell->split_cmd[0], "pwd") == 0)
		g_sh_status = ft_pwd(fd, shell);
	else if (ft_strcmp(shell->split_cmd[0], "cd") == 0)
		g_sh_status = ft_cd(shell, fd);
	else if (ft_strcmp(shell->split_cmd[0], "env") == 0)
		g_sh_status = ft_env(shell, fd);
	else if (ft_strcmp(shell->split_cmd[0], "export") == 0)
		g_sh_status = ft_export(shell, fd, 1);
	else if (ft_strcmp(shell->split_cmd[0], "unset") == 0)
		g_sh_status = ft_unset(shell, &shell->lst_env, fd);
	else if (ft_strcmp(shell->split_cmd[0], "exit") == 0)
	{
		if (fd > 2)
			return (0);
		exit_shell(shell);
	}
	else
		g_sh_status = ft_exec(shell, fd);
	printf("STATUS IS %i\n", g_sh_status);
	free_list_string(shell->split_cmd);
	return (0);
}

static int	find_pipe(t_shell *shell, char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{ 
			if (is_all_space2(str + i + 1, '|'))
				return (-2);
			if (shell->status_pipe->len > 0)
			{
				if (shell->status_pipe->lst_status[shell->status_pipe->pos++] == FALSE)
				{
					i++;
					continue;
				}
			}				
			return (i);
		}
		i++;
	}
	return (-1);
}

int	check_pipe(t_shell *shell)
{
	int pos;
	char *aux;
	
	pos = find_pipe(shell, shell->command);
	if (pos == -2)
		return (error_newline());
	if(pos > 0)
	{
		shell->parse_cmd = ft_substr(shell->command, 0, pos);
		aux = ft_substr(shell->command, pos + 1, ft_strlen(shell->command));

		if (shell->command)
			free(shell->command);
		shell->command = aux;
		return (1);
	}
	return (0);
}

