#include <minishell.h>

int	open_fd(t_shell *shell)
{
	int fd;
	
	fd = 1;
	if (shell->redic == 1)
		fd = open(shell->file, O_TRUNC | O_WRONLY | O_CREAT, 0664);
	else if (shell->redic == 2)
		fd = open(shell->file, O_APPEND| O_WRONLY | O_CREAT, 0664);
	else if (shell->redic == 3)
		fd = open(shell->file, O_RDWR);
	if (shell->parse_cmd)
	{
		free(shell->parse_cmd);
		shell->parse_cmd = NULL;
	}	
	if (fd < 0)
		return (no_file(shell->file, shell));
	return (fd);
}

int	exec_redic(t_shell *shell)
{
	int fd;

	fd = 0;
	char *aux_two;
	char *aux = ft_strdup(shell->parse_cmd);
	while (shell->parse_cmd)
	{
		fd = open_fd(shell);
		if (fd == 127)
		{
			free(aux);
			return (127);
		}	
		check_redic(shell);
		if (shell->parse_cmd)
		{
			close(fd);
			aux_two = ft_strjoin(aux, shell->parse_cmd);
			free(aux);
			aux = aux_two;
		}
	}
	
	if (shell->command)
	{
		aux_two = ft_strjoin(aux, shell->command);
		free(aux);
		aux = aux_two;
	}
	shell->parse_cmd = aux;
	if (ft_strncmp(shell->parse_cmd, "echo ", 5) == 0)
		check_command(shell, shell->p_status, 1);
	else
		check_command(shell, shell->p_status, fd);
	free(aux);
	shell->parse_cmd = NULL;
	if (shell->command)
	{
		free(shell->command);
		shell->command = NULL;
	}
	close(fd);
	return (1);
}
