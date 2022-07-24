/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-1_parsing_file.c                                 :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	find_next_word(char **command, char **file)
{
	char c;

	while (**command != '\0' && check_invisible_characters(**command))
		(*command)++;
	*file = (*command);
	while (**command != '\0' && !check_metacharacter(**command))
		(*command)++;
	c = **command;
	**command = '\0';
	return (c);
}

int	parsing_app_redir_out(char **command, t_cmd *cmd, int *trig)
{
	char	*file;
	char	c;

	parsing_invisible_characters(command, trig);
	parsing_invisible_characters(command, trig);
	c = find_next_word(command, &file);
	printf("app_file->%s\n", file);
	if (file && *file)
	{
		cmd->outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (cmd->outfile == -1)
		{
			dprintf(2,"minishell: %s: %s \n", file, strerror(errno));
			return (1);
		}
		**command = c;
		return (0);
	}
	**command = c;
	command[0][1] = '\0';
	return(130);
}

int	parsing_redir_out(char **command, t_cmd *cmd, int *trig)
{
	char	*file;
	char	c;

	parsing_invisible_characters(command, trig);
	c = find_next_word(command, &file);
	printf("outfile->%s\n", file);
	if (file && *file)
	{
		cmd->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (cmd->outfile == -1)
		{
			dprintf(2,"minishell: %s: %s \n", file, strerror(errno));
			return (1);
		}
		**command = c;
		return (0);
	}
	**command = c;
	command[0][1] = '\0';
	return(130);
}

int	parsing_redir_in(char **command, t_cmd *cmd, int *trig)
{
	char	*file;
	char	c;

	parsing_invisible_characters(command, trig);
	c = find_next_word(command, &file);
	printf("infile->%s\ncommand -> %s\n", file, *command);
	if (file && *file)
	{
		cmd->infile = open(file, O_RDONLY, 0777);
		if (cmd->infile == -1)
		{
			dprintf(2,"minishell: %s: %s \n", file, strerror(errno));
			return (1);
		}
		**command = c;
		return (0);
	}
	**command = c;
	command[0][1] = '\0';
	return (130);
}