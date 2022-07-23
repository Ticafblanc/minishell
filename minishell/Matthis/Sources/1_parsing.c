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

char	check_metacharacter(char c)
{
	if (c == '|' || c == '&' || c == '('
		|| c == ')' || c == '<' || c == '>'
		|| check_invisible_characters(c))
		return (c);
	return (0);
}

int	parsing_invisible_characters(char **command, int *trig)
{
	**command = '\0';
	// if (*trig == 0)
	// 	free(*command);
	// else
	(*trig) = 0;
	(*command)++;
	return (0);
}

int	parsing_met(char **command, t_cmd **cmd, int *nb_word, int *trig)
{
	int		status;


	if (*nb_word)
		status = 130;
	// if (*command[0] == '|' && *command[1] == '|')
	// 	status = parsing_or(cmd);
	if (**command =='|')
	 	status = parsing_pipe(cmd);
	// else if (*command[0] == '&' && *command[1] == '&')
	// 	status = parsing_and(cmd);
	// else if (tok == '(')
	// 	status =  parsing_brace(cmd);
	if (command[0][0] == '<' && command[0][1] == '<')
		status = parsing_here_doc(command, *cmd, trig);
	else if (command[0][0] == '>' && command[0][1] == '>')
		status = parsing_app_redir_out(command, *cmd, trig);
	else if (*command[0] == '>')
		status = parsing_redir_out(command, *cmd, trig);
	else if (**command == '<')
		status = parsing_redir_in(command, *cmd, trig);
	else if (check_invisible_characters(**command))
		status = parsing_invisible_characters(command, trig);
	else
		*command[1] = '\0';
	return(perror_minishell(status, *command));
}

int	add_word(char **command, t_cmd *cmd, int *nb_word, int *trig)
{
	char	c;

	cmd->cmd[*nb_word] = *command;
	c = 0;
	(*trig) = WORD;
	if ((**command == 34 || **command == 39))
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
		return(perror_minishell((int)c, *command));
	}
	(*nb_word)++;
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
	perror("minishell:");
	return (NULL);
}
