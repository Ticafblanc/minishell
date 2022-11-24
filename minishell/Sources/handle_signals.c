/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:26:31 by tonted            #+#    #+#             */
/*   Updated: 2022/11/20 12:30:35 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_prompt(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	handle_exec(int sig_num)
{
	(void) sig_num;
	close (STDOUT_FILENO);
	close (STDIN_FILENO);
	exit (EXIT_FAILURE);
}

void	handle_exe(int sig_num)
{
	if (sig_num == SIGINT)
		printf("\n");
	else
		printf("Quit: 3\n");
}
