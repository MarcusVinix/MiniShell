
#include "minishell.h"

int	status;



void	get_command(t_shell  *shell)
{
	char	cwd[2021];
	char	*prompt;
	char	*tmp;

	getcwd(cwd, 2021);
	tmp = ft_strjoin("\033[33m", cwd);
	prompt = ft_strjoin(tmp, "$\033[0m ");
	free(tmp);
	if (shell->command)
		free(shell->command);
	shell->command = readline(prompt);
	if (shell->command == NULL)
		exit_shell(shell, &status) ;
	free(prompt);
	//if (!shell->command)
	//	exit_shell(shell, &status);
	add_history(shell->command);
	shell->s_redic->redic = -1;
}

static void	start_struct(t_shell *shell, char **env)
{
	shell->s_redic = malloc(sizeof(t_redic));
	shell->command = NULL;
	shell->parse_cmd = NULL;
	shell->fd_in = 0;
	shell->fd_out = 1;
	shell->p_status = &status;
	shell->len_env = 0;
	shell->lst_env = create_bckup_env(env, shell);
	shell->s_redic->in = 0;
	shell->s_redic->out = 1;
	shell->s_redic->delimiter = NULL;
	shell->s_redic->file = NULL;
	shell->s_redic->redic = -1;
	shell->s_redic->parse = NULL;
	shell->s_redic->cmd = NULL;
}

static void reset_struct(t_shell *shell)
{
	if (shell->s_redic->delimiter != NULL)
		free(shell->s_redic->delimiter);
	if (shell->s_redic->file)
		free(shell->s_redic->file);
	if (shell->s_redic->parse)
		free(shell->s_redic->parse);
	if (shell->s_redic->cmd)
		free(shell->s_redic->cmd);
	if (shell->s_redic)
		free(shell->s_redic);
	shell->s_redic = malloc(sizeof(t_redic));
	shell->s_redic->in = 0;
	shell->s_redic->out = 1;
	shell->s_redic->redic = -1;
	shell->s_redic->delimiter = NULL;
	shell->s_redic->file = NULL;
	shell->s_redic->parse = NULL;
	shell->s_redic->cmd = NULL;
}

//signal 1 = entrou no pipe
//signal 0 = sem pipe
int	treatment_redic(t_shell *shell, int signal, int fd)
{
	if (check_redic(shell, signal))
	{
		if (signal == 1)
			shell->s_redic->out = fd;
		if (shell->s_redic->parse == NULL)
		{
			reset_struct(shell);
			return (-1);
		}
		if (exec_redic(shell))
		{
			free(shell->s_redic->parse);
			shell->s_redic->parse = NULL;
			reset_struct(shell);
			return(-1);
		}
		return (1);
	}
	return (0);
}

//fd 0 READ STDIN
//fd 1 WRITE STDOUT
static int exec_pipe(t_shell *shell)
{
	int		fd[2];

	while (shell->parse_cmd)
	{
		if (pipe(fd) >= 0)
		{
			if (treatment_redic(shell, 1, fd[1]) == 0)
				check_command(shell, &status, fd[1]);
			reset_struct(shell);
			free(shell->parse_cmd);
			dup2(fd[0], shell->fd_in);
			shell->parse_cmd = NULL;
			close(fd[0]);
			close(fd[1]);
			//printf("count %i\n", i++);
		}
		else
		{
			printf("Minishell: falha no pipe\n");
			ft_putendl_fd(strerror(errno), 2);
			return (0);
		}
		check_pipe(shell);
	}
	return (1);
}



int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	struct sigaction	act_quit;
	int		in;
	int		out;

	in = dup(0);
	out = dup(1);
	status = 0;
	if (argc != 1 || argv[1])
		return (0);
	start_struct(&shell, env);
	while (1)
	{
		config_sigaction(&shell.act, sigint_handle, SIGINT);
		config_sigaction(&act_quit, SIG_IGN, SIGQUIT);
		get_command(&shell);
		if (is_all_space(shell.command))
			continue ;
		if (check_pipe(&shell))
			if (!exec_pipe(&shell))
				continue ;
		if (treatment_redic(&shell, 0, 1) == -1)
			continue ;
		if (shell.command)
		{
			reset_struct(&shell);
			check_command(&shell, &status, 1);
		}
		dup2(in, 0);
		dup2(out, 1);
		reset_struct(&shell);
		wait(NULL);
	}
	return (status);
}
