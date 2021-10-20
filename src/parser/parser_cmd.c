
#include <minishell.h>

int	check_command(t_shell *shell, int *status, int fd)
{
	(void) fd;
	if (shell->parse_cmd)
		shell->split_cmd = ft_split(shell->parse_cmd, ' ');
	else
		shell->split_cmd = ft_split(shell->command, ' ');
	printf("teste |%s|\n", shell->split_cmd[0]);
	if (ft_strcmp(shell->split_cmd[0], "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(shell->split_cmd[0], "pwd") == 0)
		ft_pwd(shell, shell->command);
	else if (ft_strcmp(shell->split_cmd[0], "cd") == 0)
		*status = ft_cd(shell);
	else if (ft_strcmp(shell->split_cmd[0], "env") == 0)
		*status = ft_env(shell);
	else if (ft_strcmp(shell->split_cmd[0], "export") == 0)
		*status = ft_export(shell);
	else if (ft_strcmp(shell->split_cmd[0], "unset") == 0)
		*status = ft_unset(shell, &shell->lst_env);
	else if (ft_strcmp(shell->split_cmd[0], "exit") == 0)
	{
		free_all(shell);
		exit(*status);
	}
	else
		*status = ft_exec(shell);
	printf("STATUS IS %i\n", *status);
	free_list_string(shell->split_cmd);
	return (0);
}

int	check_pipe(t_shell *shell)
{
	int pos;
	char *aux;
	
	pos = find_index(shell->command, '|');
	if(pos > 0)
	{
		shell->parse_cmd = ft_substr(shell->command, 0, pos);
		aux = ft_substr(shell->command, pos + 1, ft_strlen(shell->command));
		free(shell->command);
		shell->command = aux;
		return (1);
	}
	return (0);
}



