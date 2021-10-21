
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
	if (!shell->command)
		exit(0);
	free(prompt);
	add_history(shell->command);
}

static void	start_struct(t_shell *shell, char **env)
{
	shell->command = NULL;
	shell->parse_cmd = NULL;
	shell->lst_env = create_bckup_env(env);
	shell->fd_in = 0;
	shell->fd_out = 1;
}

//fd 0 READ STDIN
//fd 1 WRITE STDOUT
static void exec_pipe(t_shell *shell)
{
	int		fd[2];

	while (shell->parse_cmd)
	{
		if (pipe(fd) >= 0)
		{
			check_command(shell, &status, fd[1]);
			
			free(shell->parse_cmd);

			dup2(fd[0], shell->fd_in);

			////dup2(fd[1], shell->fd_out);
			shell->parse_cmd = NULL;
			close(fd[0]);
			close(fd[1]);
		}
		check_pipe(shell);
	}
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
		get_command(&shell);
		if (check_pipe(&shell))
			exec_pipe(&shell);
		if (shell.command)
		{
			check_command(&shell, &status, 1);
			dup2(in, 0);
			dup2(out, 1);
			//close(shell.fd_in);
			//close(shell.fd_out);
		}
	}
	return (status);
}
