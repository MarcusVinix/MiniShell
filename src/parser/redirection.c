#include <minishell.h>

static void	store_delimiter(t_shell *shell)
{
	char	*tmp;

	if (!shell->s_redic->file)
		return ;
	if (!shell->s_redic->delimiter)
		shell->s_redic->delimiter = ft_strdup(shell->s_redic->file);
	else
	{
		tmp = ft_strjoin(shell->s_redic->delimiter, " ");
		free(shell->s_redic->delimiter);
		shell->s_redic->delimiter = NULL;
		shell->s_redic->delimiter = ft_strjoin(tmp, shell->s_redic->file);
		free(tmp);
	}
}

static int	open_fd(t_shell *shell)
{
	int fd;
	
	fd = 1;
	if (!shell->s_redic->file)
		return (2);
	if (shell->s_redic->redic == 1)
		shell->s_redic->out = open(shell->s_redic->file, O_TRUNC | O_WRONLY | O_CREAT, 0664);
	else if (shell->s_redic->redic == 2)
		shell->s_redic->out = open(shell->s_redic->file, O_APPEND| O_WRONLY | O_CREAT, 0664);
	else if (shell->s_redic->redic == 3)
		shell->s_redic->in = open(shell->s_redic->file, O_RDWR);
	else if (shell->s_redic->redic == 4)
		store_delimiter(shell);
	if (shell->s_redic->parse)
	{
		free(shell->s_redic->parse);
		shell->s_redic->parse = NULL;
	}	
	if ((shell->s_redic->redic == 1 || shell->s_redic->redic == 2) && shell->s_redic->out < 0)
		return (no_file(shell->s_redic->file, shell));
	if ((shell->s_redic->redic == 3 || shell->s_redic->redic == 4) && shell->s_redic->in < 0)
		return (no_file(shell->s_redic->file, shell));
	return (fd);
}

static int exec_heredoc(t_shell *shell)
{
	char	*line;
	char	**del_lst;
	int		i;
	int		fd;
	pid_t	pid;

	i = 0;
	config_sigaction(&shell->act, SIG_IGN, SIGINT);
	config_sigaction(&shell->act, SIG_IGN, SIGQUIT);
	fd = open("/tmp/heredoc.tmp", O_TRUNC | O_RDWR | O_CREAT, 0664);
	pid = fork();
	del_lst = ft_split(shell->s_redic->delimiter, ' ');
	if (pid == 0)
	{
		config_sigaction(&shell->act, handle_heredoc, SIGINT);
		while (1)
		{
			line = NULL;
			line = readline("> ");
			if (!line)
			{
				ft_putstr_fd("-MiniShell: warning: ", 2);
				ft_putstr_fd("here-document delimited by ", 2);
				ft_putstr_fd("end-of-file (wanted `", 2);
				ft_putstr_fd(del_lst[i++], 2);
				ft_putendl_fd("')", 2);
				if (del_lst[i])
					continue ;
				else
					break ;
			}
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
		exit(9);
	}
	waitpid(pid, shell->p_status, 0);
	free_list_string(del_lst);
	free(shell->s_redic->delimiter);
	shell->s_redic->delimiter = NULL;
	return (*shell->p_status);
}

//signal 1 = entrou no pipe
//signal 0 = sem pipe
static int	exec_redic2(t_shell *shell, char *aux)
{
	char	*aux_two;
	
	//printf("CAIU NO EXEC2\n");
	if (shell->s_redic->delimiter)
		shell->s_redic->in = open("/tmp/heredoc.tmp", O_RDONLY);
	if (shell->s_redic->cmd)
	{
		aux_two = ft_strjoin(aux, shell->s_redic->cmd);
		free(aux);
		aux = aux_two;
	}
	shell->s_redic->parse = aux;
	if (shell->s_redic->delimiter)
		if (exec_heredoc(shell) == 0)
			return (1);
	if (shell->s_redic->redic == 1 || shell->s_redic->redic == 2)
		check_command(shell, shell->p_status, shell->s_redic->out);
	else
		check_command(shell, shell->p_status, shell->s_redic->in);
	free(aux);
	shell->s_redic->parse = NULL;
	if (shell->s_redic->cmd)
	{
		free(shell->s_redic->cmd);
		shell->s_redic->cmd = NULL;
	}
	return (0);
}

//signal 1 = entrou no pipe
//signal 0 = sem pipe
int	exec_redic(t_shell *shell)
{
	char	*aux_two;
	char	*aux;
	
	//printf("CAIU NO EXEC\n");
	aux = ft_strdup(shell->s_redic->parse);
	while (shell->s_redic->parse)
	{
		if (open_fd(shell) == 127)
		{
			free(aux);
			return (127);
		}
		if (check_redic(shell, 2) == 2)
		{
			free(aux);
			free(shell->s_redic->parse);
			shell->s_redic->parse = NULL;
			return (error_newline(shell));
		}
		if (shell->s_redic->parse)
		{
			aux_two = ft_strjoin(aux, shell->s_redic->parse);
			free(aux);
			aux = aux_two;
		}
	}
	if (exec_redic2(shell, aux))
		return (1);
	return (0);
}

