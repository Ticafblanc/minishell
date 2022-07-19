/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main.c                                           :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/11 18:30:06 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	reset_command(char **command)
{
	if (!*command)
		return ;
	free(*command);
	*command = NULL;
}

int	prompt(char *prompt, int *status)
{
	signal(SIGINT, handle_prompt);
	signal(SIGQUIT, SIG_IGN);
	command = readline(prompt);
	if (!*command)
		free_and_exit(EXIT_SUCCESS);
	else if (command[0] != '\0')
	{
		add_history(command);
		status = execute(command, status);
	}
	reset_command(&command);
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		status;
	char	*command;
	
	pid = fork();
	if (pid < 0)
		exit(ECHILD);
	if (!pid)
	{
		status = init_minishell(envp);
		if (argc == 1 && !status)
		{
			while (argc)
			{
				prompt("minishell %", &status);// voir si util p[ar la suite le status
			}
		}
		if (argc > 2 && ft_strncmp(argv[1], "-c", 2) == 0 && && !status)
			free_and_exit(execute(argv[2], &status));
		free_and_exit(status);
	}
	waitpid(pid, &status, 0);
	exit(status);
}
