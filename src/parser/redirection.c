#include <minishell.h>

static void	store_delimiter(t_shell *shell)
{
	char	*tmp;
	
	if (!shell->file)
		return ;
	if (!shell->delimiter)
		shell->delimiter = ft_strdup(shell->file);
	else
	{
		tmp = ft_strjoin(shell->delimiter, " ");
		free(shell->delimiter);
		shell->delimiter = ft_strjoin(tmp, shell->file);
		free(tmp);
	}
}

static int	open_fd(t_shell *shell)
{
	int fd;
	
	fd = 1;
	if (shell->redic == 1)
		fd = open(shell->file, O_TRUNC | O_WRONLY | O_CREAT, 0664);
	else if (shell->redic == 2)
		fd = open(shell->file, O_APPEND| O_WRONLY | O_CREAT, 0664);
	else if (shell->redic == 3)
		fd = open(shell->file, O_RDWR);
	else if (shell->redic == 4)
		store_delimiter(shell);
	if (shell->parse_cmd)
	{
		free(shell->parse_cmd);
		shell->parse_cmd = NULL;
	}	
	if (fd < 0)
		return (no_file(shell->file, shell));
	return (fd);
}

static void exec_heredoc(t_shell *shell)
{
	char	*line;
	char	**del_lst;
	int		fd;
	int		i;
	
	i = 0;
	fd = open("/tmp/heredoc.tmp", O_TRUNC | O_RDWR | O_CREAT, 0664);
	del_lst = ft_split(shell->delimiter, ' ');
	while (1)
	{
		line = NULL;
		line = readline("> ");
		if (ft_strcmp(line, del_lst[i]) == 0)
		{
			if (del_lst[i + 1] != NULL)
				i++;
			else
			{
				free (line);
				break ;
			}
		}
		else if (del_lst[i + 1] == NULL)
			ft_putendl_fd(line, fd);
		free(line);
	}
	dup2(fd, shell->fd_in);
	close(fd);
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
	if (shell->delimiter)
		exec_heredoc(shell);
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

