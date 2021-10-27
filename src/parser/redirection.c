#include <minishell.h>

int	open_fd(t_shell *shell)
{
	int fd;
	
	fd = -1;
	if (shell->redic == 1)
		fd = open(shell->file, O_WRONLY | O_CREAT);
	else if (shell->redic == 2)
		fd = open(shell->file, O_WRONLY | O_APPEND | O_CREAT);
	free(shell->file);
	shell->file = NULL;
	return (fd);
}

int	exec_redic(t_shell *shell)
{
	int fd;

	fd = 0;
	char *aux = ft_strdup(shell->parse_cmd);
	while (shell->parse_cmd)
	{
		fd = open_fd(shell);
		if (shell->parse_cmd)
		{
			free(shell->parse_cmd);
			shell->parse_cmd = NULL;
		}			
		check_redic(shell);
		if (shell->parse_cmd)
			close(fd);
	}
	shell->parse_cmd = aux;
	check_command(shell, shell->p_status, fd);
	free(aux);
	shell->parse_cmd = NULL;
	if (shell->command)
	{
		free(shell->command);
		shell->command = NULL;
		printf("CAI AQ no redic\n");
	}
	close(fd);
	return (1);
}
