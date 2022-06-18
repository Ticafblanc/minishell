/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_signal.c                                         :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_global	g_global;

void	monitor_sigint(int sig_num)
{
	if (sig_num == SIGINT)
	{
		//g_global.statut = EXIT_FAILURE;
		//ioctl(STDIN_FILENO, TIOCSTI, "\b");
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		//rl_replace_line("", 0);
		rl_on_new_line();
		//sig_num = 0;
	}
	//g_global.statut = EXIT_FAILURE;
}
