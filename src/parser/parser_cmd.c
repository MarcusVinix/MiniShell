
#include <minishell.h>

int	check_command(t_shell *shell, int *status, int fd)
{
	if (shell->parse_cmd)
		shell->split_cmd = ft_split(shell->parse_cmd, ' ');
	else
		shell->split_cmd = ft_split(shell->command, ' ');
	printf("teste |%s|\n", shell->split_cmd[1]);
	if (ft_strcmp(shell->split_cmd[0], "echo") == 0)
		ft_echo(shell, fd);
	else if (find_index(shell->split_cmd[0], '=') > 0)
		ft_export(shell, fd, 0);
	else if (ft_strcmp(shell->split_cmd[0], "pwd") == 0)
		ft_pwd(fd);
	else if (ft_strcmp(shell->split_cmd[0], "cd") == 0)
	 	*status = ft_cd(shell, fd);
	else if (ft_strcmp(shell->split_cmd[0], "env") == 0)
		*status = ft_env(shell, fd);
	else if (ft_strcmp(shell->split_cmd[0], "export") == 0)
		*status = ft_export(shell, fd, 1);
	else if (ft_strcmp(shell->split_cmd[0], "unset") == 0)
		*status = ft_unset(shell, &shell->lst_env, fd);
	else if (ft_strcmp(shell->split_cmd[0], "exit") == 0)
	{
		if (fd > 2)
			return (0);
		exit_shell(shell, status);
	}
	else
		*status = ft_exec(shell, fd);
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
		if (shell->command)
			free(shell->command);
		shell->command = aux;
		return (1);
	}
	return (0);
}

static int	find_redic(t_shell *shell)
{
	int i;
	char *aux;

	if (!shell->command)
		return (-1);
	aux = shell->command;
	i = 0;
	while (aux[i])
	{
		if (aux[i] == '>')
		{
			if(aux[i + 1] == '>')
				shell->redic = 2;
			else
				shell->redic = 1;
			return (i);
		}
		else if (aux[i] == '<')
		{
			if (aux[i + 1] == '<')
				shell->redic = 4;
			else
				shell->redic = 3;
			return (i);
		}
		i++;
	}
	return (-1);
}

char	*find_file(t_shell *shell, int *pos)
{
	char	*aux;
	char	*file;
	int		i;

	i = *pos + 1;
	aux = shell->command;
	while (aux[i])
	{
		if (aux[i] == ' ')
			break ;
		i++;
	}
	file = ft_substr(aux, *pos, i);
	*pos = i;
	return (file);
}

int check_redic(t_shell *shell)
{
	int pos;
	char *aux;

	pos = find_redic(shell);
	if (pos > 0)
	{
		printf("CAIU NA ONDE TEM REDIC\n");
		shell->parse_cmd = ft_substr(shell->command, 0, pos);
		shell->file = find_file(shell, &pos);
		aux = ft_substr(shell->command, pos + 1, ft_strlen(shell->command));
		if(shell->command)
		{
			free(shell->command);
			shell->command = NULL;
		}
		shell->command = aux;
		return (1);
	}
	return (0);
}
