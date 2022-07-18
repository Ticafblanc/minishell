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

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	int		status;
	char	*command;
	

	if (argc == 3 && ft_strncmp(argv[1], "-c", 2) == 0)
			free_and_exit(exec(argv[2]));
	else if (argc == 1)
	{
		status = init_minishell(envp);
		while (status == ON)
		{
			signal(SIGINT, handle_prompt);
			signal(SIGQUIT, SIG_IGN);
			command = readline(prompt);
			if (!*command)
				free_and_exit(EXIT_SUCCESS);
			else if (command[0] != '\0')
			{
				add_history(command);
				exec(command, MAIN);
			}   
			reset_command(&command);
		}
	}
	else
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}
