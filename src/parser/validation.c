#include "minishell.h"

int valid_redic(char *cmd, int pos)
{
	int		i;

	i = 0;
	if (!cmd)
		return (0);
	printf("cmd monstro %c\n", cmd[pos]);
	if (cmd[pos] == '<')
	{
		if (cmd[pos + 1] == '<')
			pos++;
		if (is_all_space2(cmd + pos + 1, '<'))
			return (0);
	}
	else if (cmd[pos] == '>')
	{
		if (cmd[pos + 1] == '>')
			pos++;
		if (is_all_space2(cmd + pos + 1, '>'))
			return (0);
	}
	return(1);
}
