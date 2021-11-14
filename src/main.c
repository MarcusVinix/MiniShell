
#include "minishell.h"

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
	if (shell->command == NULL)
		exit_shell(shell);
	add_history(shell->command);
	shell->s_redic->redic = -1;
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
			set_free_and_null(&shell->parse_cmd);
			return (-1);
		}
		if (exec_redic(shell))
		{
			set_free_and_null(&shell->parse_cmd);
			reset_struct(shell);
			return(-1);
		}
		if (signal == 0)
		{
			set_free_and_null(&shell->s_redic->parse);
			set_free_and_null(&shell->command);
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
	int		res;

	res = 0;
	while (shell->parse_cmd)
	{
		if (pipe(fd) >= 0)
		{
			res = treatment_redic(shell, 1, fd[1]);
			if (res == -1)
				return (0);
			if (res == 0)
				check_command(shell, fd[1]);
			reset_struct(shell);
			set_free_and_null(&shell->parse_cmd);
			dup2(fd[0], shell->fd_in);
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
		if (check_pipe(shell) == -1)
			return (0);
	}
	return (1);
}



int	main(int argc, char **argv, char **env)
{
	t_shell	shell;
	struct sigaction	act_quit;
	int		in;
	int		out;
	int		res;

	res = 0;
	in = dup(0);
	out = dup(1);
	sh_status = 0;
	if (argc != 1 || argv[1])
		return (0);
	start_struct(&shell, env);
	while (1)
	{
		config_sigaction(&shell.act, sigint_handle, SIGINT);
		config_sigaction(&act_quit, SIG_IGN, SIGQUIT);
		dup2(in, 0);
		dup2(out, 1);
		get_command(&shell);
		if (is_all_space(shell.command))
			continue ;
		if (trating_quotes(&shell))
			continue ;
		res = check_pipe(&shell);
		if (res == -1)
			continue ;
		if (res)
			if (!exec_pipe(&shell))
				continue ;
		if (treatment_redic(&shell, 0, 1) == -1)
			continue ;
		if (shell.command)
		{
			reset_struct(&shell);
			check_command(&shell, 1);
		}
		shell.status_pipe->len = 0;
		shell.status_pipe->pos = 0;
		reset_struct(&shell);
	}
	return (sh_status);
}
