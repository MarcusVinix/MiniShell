
#include <minishell.h>

int	check_command(t_shell *shell, int *status, int fd)
{
	if (shell->parse_cmd)
		shell->split_cmd = ft_split(shell->parse_cmd, ' ');
	else
		shell->split_cmd = ft_split(shell->command, ' ');
	printf("teste |%s|\n", shell->split_cmd[0]);
	if (ft_strcmp(shell->split_cmd[0], "echo") == 0)
		ft_echo(shell, fd);
	else if (find_index(shell->split_cmd[0], '=') > 0)
		ft_export(shell, fd, 0);
	else if (ft_strcmp(shell->split_cmd[0], "pwd") == 0)
		ft_pwd(fd, shell);
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
				shell->s_redic->redic = 2;
			else
				shell->s_redic->redic = 1;
			return (i);
		}
		else if (aux[i] == '<')
		{
			if (aux[i + 1] == '<')
				shell->s_redic->redic = 4;
			else
				shell->s_redic->redic = 3;
			return (i);
		}
		i++;
	}
	return (-1);
}

char	*ft_split_rev(char **split)
{
	char	*tmp;
	char	*tmp2;
	char	*str;
	int		i;

	if (!split)
		return (NULL);
	str = ft_strjoin(split[0], " ");
	i = 1;
	while (split[i])
	{
		tmp = ft_strjoin(str, split[i]);
		free(str);
		str = tmp;
		if (split[++i])
		{
			tmp2 = ft_strjoin(str, " ");
			free(str);
			str = tmp2;
		}
	}
	return (str);
}

char	*find_file(t_shell *shell, int *pos)
{
	char	**aux;
	char	*file;
	char	*tmp;

	if (shell->s_redic->redic == 1 || shell->s_redic->redic == 3)
		tmp = ft_substr(shell->command, *pos + 1, ft_strlen(shell->command));
	else
		tmp = ft_substr(shell->command, *pos + 2, ft_strlen(shell->command));
	aux = ft_split(tmp, ' ');
	file = ft_strdup(aux[0]);
	*pos = ft_strlen(file);
	if (shell->command)
		free(shell->command);
	shell->command = ft_split_rev(aux);
	free_list_string(aux);
	free(tmp);
	return (file);
}

int check_redic(t_shell *shell)
{
	int pos;
	char *aux;

	pos = find_redic(shell);
	if (pos >= 0)
	{
		shell->parse_cmd = ft_substr(shell->command, 0, pos);
		if (shell->s_redic->file)
			free(shell->s_redic->file);
		shell->s_redic->file = find_file(shell, &pos);
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
