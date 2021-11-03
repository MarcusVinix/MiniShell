
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
}

static void reset_struct(t_shell *shell)
{
	if (shell->s_redic->delimiter != NULL)
		free(shell->s_redic->delimiter);
	if (shell->s_redic->file)
		free(shell->s_redic->file);
	if (shell->s_redic)
		free(shell->s_redic);
	shell->s_redic = malloc(sizeof(t_redic));
	shell->s_redic->in = 0;
	shell->s_redic->out = 1;
	shell->s_redic->redic = -1;
	shell->s_redic->delimiter = NULL;
	shell->s_redic->file = NULL;
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
			check_command(shell, &status, fd[1]);
			free(shell->parse_cmd);
			dup2(fd[0], shell->fd_in);
			shell->parse_cmd = NULL;
			close(fd[0]);
			close(fd[1]);
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
		signal(SIGINT, sigint_handle);
		signal(SIGQUIT, sigquit_handle);
		get_command(&shell);
		if (is_all_space(shell.command))
			continue ;
		if (check_pipe(&shell))
			if (!exec_pipe(&shell))
				continue ;
		if (check_redic(&shell))
		{
			if (shell.parse_cmd == NULL)
			{
				reset_struct(&shell);
				continue ;
			}
			if (exec_redic(&shell))
			{
				free(shell.parse_cmd);
				shell.parse_cmd = NULL;
				reset_struct(&shell);
				continue ;
			}
		}
		if (shell.command)
			check_command(&shell, &status, 1);
		dup2(in, 0);
		dup2(out, 1);
		reset_struct(&shell);
	}
	return (status);
}
