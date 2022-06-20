/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-2-0_execute.c                                    :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_global	g_global;

static int	check_output_character(char *command, t_command *cmd, char end)
{
	int	i;

	i = 0;
	cmd->flag_end = STDIN_FILENO;
	while (command[i] != end)
	{
		if (command[i] == '|' && command [i + 1] == '|')
		{
			cmd->flag_end = OR;
			return (i);
		}	
		if (command[i] == '&' && command [i + 1] == '&')
		{
			cmd->flag_end = AND;
			return (i);
		}	
		if (command[i] == '|')
		{
			cmd->flag_end = PIPE;
			return (i);
		}	
		if (command[i] == '(')
			return (i);
		else
            i++;
	}
	return (i);
}

static char	*find_command(char *command, t_command *cmd, char end)
{
	int i;

	i = check_output_character(command, cmd, end);
    if (command[i] == '(' && i == 0)
		command = execute_command(command + 1, ')');
	else if (i > 0)
	{
		cmd->to_do = ft_substr(command, 0, i);
		if (!cmd->to_do)
			free_and_exit(MEMO);
	}
	printf("\n ==>cmd a executer : %s\n", cmd->to_do); //test du presorte commande
	if (cmd->flag_end == AND || cmd->flag_end == OR)
		command += i + 2;
	if (cmd->flag_end == PIPE)
		command += ++i;
	return (command);
}

char	*execute_command(char *command, char end)
{
	t_command	cmd;

	cmd.flag_start = STDIN_FILENO;
	cmd.flag_end = STDOUT_FILENO;
	cmd.infile = 0;
	cmd.outfile = 1;
	signal(SIGINT, handle_execute);
	signal(SIGQUIT, SIG_DFL);
	while (*command != end)
	{
		while (check_invisible_characters(*command))
			command++;
		printf("\n !!!!command a executer : %s\n", command);
		command = find_command(command, &cmd, end);
		printf("\n command a executer : %s!!!!!!\n", command);
		//parse_command(cmd);
		//dispatch_execute(&cmd);
	}
	if (end == '\0')
		exit(EXIT_SUCCESS);
	return (command);
}
