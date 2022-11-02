/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/10/18 19:29:40 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	minishell_loop(char ***envp)
{
	char	*command;

	while (42)
	{
		signal(SIGINT, handle_prompt);
		signal(SIGQUIT, SIG_IGN);
		command = readline(PROMPT);
		if (!command)
			exit(exit_free_envp(envp));
		//signal(SIGINT, handle_prompt);
		if (*command != '\0')
			execute(command, envp);
		else
			add_history(command);
		free_null((void *)command);
		*last_status() = get_value_status();
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (!envp || !(*envp))
	{
		printf("minshell: minishell can't be launch without environement\n");
		return (EXIT_SUCCESS);
	}
	if (argc == 1)
	{
		if (init(&envp))
			exit(perror_minishell(errno, "minishell:"));
		minishell_loop(&envp);
	}
	else if (argc > 1 && ft_strncmp(argv[1], "-c", 2) == 0)
		exit(execute(argv[2], &envp));
	dprintf(2, "minshell: %s: invalid option\n"
		"Usage: minishell [option] [command]\n"
		"Shell option :\n\t-c command\n", argv[1]);
	exit(2);
}
