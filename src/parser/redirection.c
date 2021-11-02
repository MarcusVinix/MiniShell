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
	if (shell->s_redic->redic == 1)
		shell->s_redic->out = open(shell->s_redic->file, O_TRUNC | O_WRONLY | O_CREAT, 0664);
	else if (shell->s_redic->redic == 2)
		shell->s_redic->out = open(shell->s_redic->file, O_APPEND| O_WRONLY | O_CREAT, 0664);
	else if (shell->s_redic->redic == 3)
		shell->s_redic->in = open(shell->s_redic->file, O_RDWR);
	else if (shell->s_redic->redic == 4)
		store_delimiter(shell);
	if (shell->parse_cmd)
	{
		free(shell->parse_cmd);
		shell->parse_cmd = NULL;
	}	
	if ((shell->s_redic->redic == 1 || shell->s_redic->redic == 2) && shell->s_redic->out < 0)
		return (no_file(shell->s_redic->file, shell));
	if ((shell->s_redic->redic == 3 || shell->s_redic->redic == 4) && shell->s_redic->in < 0)
		return (no_file(shell->s_redic->file, shell));
	return (fd);
}

static void exec_heredoc(t_shell *shell)
{
	char	*line;
	char	**del_lst;
	int		i;
	int		fd;

	i = 0;
	fd = open("/tmp/heredoc.tmp", O_TRUNC | O_RDWR | O_CREAT, 0664);
	del_lst = ft_split(shell->s_redic->delimiter, ' ');
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
	free_list_string(del_lst);
	free(shell->s_redic->delimiter);
	shell->s_redic->delimiter = NULL;
}

void	exec_redic2(t_shell *shell, char *aux)
{
	char	*aux_two;
	
	if (shell->s_redic->delimiter)
		shell->s_redic->in = open("/tmp/heredoc.tmp", O_RDONLY);
	if (shell->command)
	{
		aux_two = ft_strjoin(aux, shell->command);
		free(aux);
		aux = aux_two;
	}
	shell->parse_cmd = aux;
	if (shell->s_redic->delimiter)
		exec_heredoc(shell);
	if (shell->s_redic->redic == 1 || shell->s_redic->redic == 2)
		check_command(shell, shell->p_status, shell->s_redic->out);
	else
		check_command(shell, shell->p_status, shell->s_redic->in);
	free(aux);
	shell->parse_cmd = NULL;
	if (shell->command)
	{
		free(shell->command);
		shell->command = NULL;
	}
}

int	exec_redic(t_shell *shell)
{
	char	*aux_two;
	char	*aux;
	
	aux = ft_strdup(shell->parse_cmd);
	while (shell->parse_cmd)
	{
		if (open_fd(shell) == 127)
		{
			free(aux);
			return (127);
		}	
		check_redic(shell);
		printf("parse |%s|\n", shell->parse_cmd);
		if (shell->parse_cmd)
		{
			printf("entrei\n");
			aux_two = ft_strjoin(aux, shell->parse_cmd);
			free(aux);
			aux = aux_two;
			// if (shell->s_redic->redic == 1 || shell->s_redic->redic == 2)
			// 	close(shell->s_redic->out);
			// if (shell->s_redic->redic == 3)
			// 	close(shell->s_redic->in);
		}
	}
	exec_redic2(shell, aux);
	return (1);
}

