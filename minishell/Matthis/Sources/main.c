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
	
<<<<<<< HEAD

	if (argc == 3 && ft_strncmp(argv[1], "-c", 2) == 0)
	{
		pid = fork();
		if (pid < 0)
			free_and_exit(FORK);
		else if (!pid)
			exec(argv[2]);
		waitid(pid, &status, 0);//voir si retour satus code est coerrect
	}		
	else if (argc == 1)
=======
	pid = fork();
	if (pid < 0)
		exit(ECHILD);
	if (!pid)
>>>>>>> origin/school
	{
		status = init_minishell(envp);
		if (argc == 1 && !status)
		{
<<<<<<< HEAD
			signal(SIGINT, handle_prompt);
			signal(SIGQUIT, SIG_IGN);
			command = readline("minishell %");
			if (!*command)
				free_and_exit(EXIT_SUCCESS);
			else if (command[0] != '\0')
=======
			while (argc)
>>>>>>> origin/school
			{
				prompt("minishell %", &status);// voir si util p[ar la suite le status
			}
		}
		if (argc > 2 && ft_strncmp(argv[1], "-c", 2) == 0 && && !status)
			free_and_exit(execute(argv[2], &status));
		free_and_exit(status);
	}
<<<<<<< HEAD
	else
		exit(EXIT_FAILURE);//print erreru argument
	exit(status);//voir satuts code
=======
	waitpid(pid, &status, 0);
	exit(status);
>>>>>>> origin/school
}
