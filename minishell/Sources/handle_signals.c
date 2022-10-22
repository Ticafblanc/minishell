/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 16:26:31 by tonted            #+#    #+#             */
/*   Updated: 2022/10/14 16:27:13 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

<<<<<<<< HEAD:libft/Sources/3_signal.c
#include <minishell.h>
========
#include "minishell.h"
>>>>>>>> origin/ours🧸:minishell/Sources/handle_signals.c

void	handle_prompt(int sig_num)
{
	if (sig_num == SIGINT)
	{		
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}// prevoir switch pour sig action

<<<<<<<< HEAD:libft/Sources/3_signal.c
// void	handle_execute(int sig_num)
// {
// 	if (sig_num == SIGINT)
// 	{
// 		exit(EXIT_SUCCESS);
// 		//ioctl(STDIN_FILENO, TIOCSTI, "\n");
// 		//rl_replace_line("", 0);
// 		//rl_on_new_line();
// 	}
// }
  
========
void	handle_exec(int sig_num)
{
	if (sig_num == SIGINT)
		exit(EXIT_FAILURE);
}
>>>>>>>> origin/ours🧸:minishell/Sources/handle_signals.c
