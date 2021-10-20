
#include "minishell.h"

int	status;

void	get_command(t_shell  *shell)
{
	char	cwd[2021];
	char	*prompt;
	char	*tmp;
	int		ret;

	getcwd(cwd, 2021);
	tmp = ft_strjoin("\033[33m", cwd);
	prompt = ft_strjoin(tmp, "$\033[0m ");
	free(tmp);
	if (shell->command)
		free(shell->command);
	shell->command = readline(prompt);
	ret = 0;
	free(prompt);
	add_history(shell->command);
}

static void	start_struct(t_shell *shell, char **env)
{
	shell->command = NULL;
	shell->parse_cmd = NULL;
	shell->lst_env = create_bckup_env(env);
}

static void exec_pipe(t_shell *shell)
{
	int		fd[2];
	//pid_t	pid;

	while (shell->parse_cmd)
	{
		//pipe(fd);
		//pid = fork();
		//if (pid == 0)
		//{
			close(fd[0]);
			//code for child
			check_command(shell, &status, fd[1]);
			free(shell->parse_cmd);
			shell->parse_cmd = NULL;
		//}
		//else 
		//{
		//	//code for father
		//}
		
		check_pipe(shell);
	}
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
		check_command(&shell, &status, 1);
	}
	return (status);
}
