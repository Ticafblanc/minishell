/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_signal.c                                         :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_prompt(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}// prevoir switch pour sig action

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
  