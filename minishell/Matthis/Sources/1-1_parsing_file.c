/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-2-1_parsing.c                                    :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	parsing_file2(char **command, t_cmd *cmd, int *trig)
{
	close(fd[FD_READ]);
		if (**command == '<')
		{
			**command = '\0';
			(*command)++;
			if (**command == '<')
				cmd->infile = open()
			else
				fofof
		}
		else
		{
			**command = '\0';
			(*command)++;
		if (**command == '>')
			cmd->outfile = open(find_next)
		else
			cmd->outfile = open
		if (check_limiter(fd[FD_WRITE], limiter) == 1)
			exit(EXIT_SUCCESS);

}

int	parsing_file(char **command, t_cmd *cmd, int *trig)
{
	int		status;
	int		next_token;
	char	*file;

	next_token = find_next_token(*command);
	file = 
	{
		*command[next_token] = '\0';
		close(fd[FD_READ]);
		parsing_file2(char **command, t_cmd *cmd, int *trig)
		
	}
	{
		close(fd[FD_WRITE]);
	}
	
	(*command) += next_token;
	(*trig) = 0;
	return (status);
}


	else if (*command[0] == '<' && *command[1] == '<')
		status =parsing_here_doc(cmd);
	else if (*command[0] == '>' && *command[1] == '>')
		status =parsing_app_redir_out;
	else if (*command[0] == '>')
		status =parsing_redir_out;
	else if (*command[0] == '<')
		status =parsing_redir_in;
	else
		*command[1] = '\0'l;

