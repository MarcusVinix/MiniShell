
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
	printf("COMANNDO ANTES\n");
	shell->command = readline(prompt);
	if (shell->command)
		printf("mano brow\n");
	printf("COMANNDO depois\n");
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
			printf("TESTE\n");
			check_command(shell, &status, fd[1]);
			printf("TESTE2\n");
			
			free(shell->parse_cmd);
			printf("TESTE3\n");

			dup2(fd[0], shell->fd_in);
			printf("TESTE4\n");
			
			//dup2(fd[1], shell->fd_out);
			printf("foir\n");
			shell->parse_cmd = NULL;
			close(fd[0]);
			close(fd[1]);
		}
		check_pipe(shell);
	}
	printf("foir\n");
}
int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

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
			printf("ENTREI NO PAdrão\n");
			check_command(&shell, &status, 1);
		}
	}
	return (status);
}
