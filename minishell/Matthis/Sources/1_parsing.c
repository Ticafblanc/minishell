/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parsing.c                                        :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parsing_met(char **command, t_cmd *cmd, int *nb_word, int *trig)
{
	char	tok;
	int		status;

	// if (*command[0] == '|' && *command[1] == '|')
	// 	status = parsing_or(cmd);
	// else if (**command =='|')
	// 	status =parsing_pipe(cmd);
	// else if (*command[0] == '&' && *command[1] == '&')
	// 	status =parsing_and(cmd);
	// else if (tok == '(')
	// 	status =parsing_brace(cmd);
	// else if (*command[0] == '<' && *command[1] == '<')
	// 	status =parsing_here_doc(cmd);
	// else if (*command[0] == '>' && *command[1] == '>')
	// 	status =parsing_app_redir_out;
	// else if (*command[0] == '>')
	// 	status =parsing_redir_out;
	if (*command[0] == '<')
		status =parsing_redir_in(char **command, t_cmd *cmd, char *command);
	else
		*command[1] = '\0';
	status = perror_minishell(130, *command)
	return(EXIT_SUCCESS);
}

int	add_word(char **command, t_cmd *cmd, int *nb_word, int *trig)
{
	char	c;

	cmd->cmd[*nb_word] = *command;
	c = 0;
	if ((*command == 34 || *command == 39))
	{
		c = **command;
		while (**command != '\0')
		{
			(*command)++;
			if (**command == c)
			{
				(*command)++;
				c = 0;
				break;
			}
		}
	}
	(*nb_word)++;
	(*trig) = WORD;
	(*command)++;
	return ((int)c);
}

t_cmd	*ft_mlstadd(t_cmd *cmd, int *status)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new)
	{
		new->cmd = (char **)ft_calloc(20, sizeof(char *));
		if (new->cmd)
		{
			new->next = NULL;
			new->ctrl_op = END;
			new->infile = READ_END;
			new->outfile = WRITE_END;
			if (cmd)
				cmd->next = new;
			return (new);
		}
		free(new);
	}
	*status = errno;
	perror("minishell:")
	return (NULL);
}
