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
		set_free_and_null(&shell->s_redic->delimiter);
		shell->s_redic->delimiter = ft_strjoin(tmp, shell->s_redic->file);
		free(tmp);
	}
}

static int	open_fd(t_shell *shell)
{
	int	fd;

	fd = 1;
	if (!shell->s_redic->file)
		return (2);
	if (shell->s_redic->redic == 1)
		shell->s_redic->out = open(shell->s_redic->file, O_TRUNC | O_WRONLY
				| O_CREAT, 0664);
	else if (shell->s_redic->redic == 2)
		shell->s_redic->out = open(shell->s_redic->file, O_APPEND
				| O_WRONLY | O_CREAT, 0664);
	else if (shell->s_redic->redic == 3)
		shell->s_redic->in = open(shell->s_redic->file, O_RDWR);
	else if (shell->s_redic->redic == 4)
		store_delimiter(shell);
	if (shell->s_redic->parse)
		set_free_and_null(&shell->s_redic->parse);
	if ((shell->s_redic->redic == 1 || shell->s_redic->redic == 2)
		&& shell->s_redic->out < 0)
		return (no_file(shell->s_redic->file, shell));
	if ((shell->s_redic->redic == 3 || shell->s_redic->redic == 4)
		&& shell->s_redic->in < 0)
		return (no_file(shell->s_redic->file, shell));
	return (fd);
}

int	aux_heredoc(char **del_lst, int *i, int fd)
{
	char	*line;

	printf(": %i\n", *i);
	line = readline("> ");
	if (!line)
	{
		printf("fora: %i\n", *i);
		if (error_heredoc(del_lst, i))
		{
			printf("dentro: %i\n", *i);
			return (1);
		}
		return (0);
	}
	if (ft_strcmp(line, del_lst[*i]) == 0)
	{
		if (del_lst[*i + 1] != NULL)
			*i += 1;
		else
		{
			set_free_and_null(&line);
			return (1);
		}
	}
	else if (del_lst[*i + 1] == NULL)
		ft_putendl_fd(line, fd);
	set_free_and_null(&line);
	return (0);
}

static void	exec_heredoc(t_shell *shell)
{
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
	printf("lsty: %i\n",ft_strlen_split(del_lst));
	if (pid == 0)
	{
		dup2(shell->in, 0);
		config_sigaction(&shell->act, handle_heredoc, SIGINT);
		while (1)
			if (aux_heredoc(del_lst, &i, fd))
				break ;
		exit(0);
	}
	waitpid(pid, &shell->ret, 0);
	g_sh_status = WEXITSTATUS(shell->ret);
	free_list_string(del_lst);
	set_free_and_null(&shell->s_redic->delimiter);
}

//signal 1 = entrou no pipe
//signal 0 = sem pipe
static int	exec_redic2(t_shell *shell, char *aux)
{
	char	*aux_two;

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
		exec_heredoc(shell);
	if (shell->s_redic->redic == 1 || shell->s_redic->redic == 2)
		check_command(shell, shell->s_redic->out);
	else
		check_command(shell, shell->s_redic->in);
	free(aux);
	shell->s_redic->parse = NULL;
	if (shell->s_redic->cmd)
		set_free_and_null(&shell->s_redic->cmd);
	return (0);
}

void	new_join(char **aux, char *str)
{
	char	*aux_two;

	aux_two = ft_strjoin(*aux, str);
	set_free_and_null(aux);
	*aux = aux_two;
}

//signal 1 = entrou no pipe
//signal 0 = sem pipe
int	exec_redic(t_shell *shell)
{
	char	*aux;

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
			set_free_and_null(&shell->s_redic->parse);
			return (2);
		}
		if (shell->s_redic->parse)
			new_join(&aux, shell->s_redic->parse);
	}
	exec_redic2(shell, aux);
	return (0);
}
