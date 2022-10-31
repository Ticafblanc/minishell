/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:26:31 by tonted            #+#    #+#             */
/*   Updated: 2022/10/26 13:18:11 by tonted           ###   ########.fr       */
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
	if (sig_num == SIGINT)
		exit(EXIT_FAILURE);
	else if (sig_num == SIGPIPE)
		exit(EXIT_FAILURE);
}

