/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_start.c                                          :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_global	g_global;

static void	reset_command(void)
{
	if (!g_global.command)
		return ;
	free(g_global.command);
	g_global.command = NULL;
}

void	start_minishell(void)
{
	pid_t	pid;
	int		statut;

	while (g_global.statut == ON)
	{
		signal(SIGINT, handle_prompt);
		signal(SIGQUIT, SIG_IGN);
		if (prompt_minishell() == 1)
		{
			pid = fork();
			if (pid == -1)
				free_and_exit(FORK);
			if (!pid)
				execute_command(g_global.command, '\0');
			waitpid(pid, &statut, 0);
		}
		reset_command();
	}
}
