/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-1-2-0_execute.c                                  :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_global	g_global;

// static int  select_flag_end(char *end)
// {
//     if (ft_strncmp(end, "||", 2) == 0)
//         return (OR);
// 	if (ft_strncmp(end, "|", 1) == 0)
//         return (PIPE);
// 	if (ft_strncmp(end, "&&", 2) == 0)
//         return (AND);
// 	if (ft_strncmp(end, "&&", 2) == 0)
//         return (AND);
// 	if (ft_strncmp(end, ">>", 2) == 0)
//         return (APPEND_FILE);
// 	if (ft_strncmp(end, ">", 1) == 0)
//         return (REPLACE_FILE);
// 	return (END_ERR);
// }

// static void	execute_brace(char *command)
// {
// 	int 	i;
// 	char	*new_command;

// 	i = 0;
// 	while (command[i] && command[i] != ')')
// 			i++;
// 	if (--i > 0)
// 	{
// 		new_command = ft_substr(command, 0, i);
// 		if (!new_command)
// 			free_and_exit(FORK);
// 	}
// 	execute_command(new_command);
// 	return (i + 2);
// }

// static void	add_outfile_name(char *command, int flag_end)
// {
// 	int 	i;
	
// 	if (flag_end == APPEND_FILE)
// 		i = 2;
// 	if (cmd->flag_end == REPLACE_FILE)
// 		i = 1;
// 	while (check_invisible_characters(command[i]))
// 			i++;
// 	while (!check_invisible_characters(command[i]))
// 			i++;
// 	return (i + 1);
// }

// static int	find_command(char *command, t_command *cmd)
// {
// 	int i;

// 	i = check_output_character(command);
//     if (g_global.command[i] == '(')
// 	{
//     	command += execute_brace(command + i + 1);
// 		find_command(command, cmd);
// 	}
// 	cmd->flag_end = select_flag_end(command + i)
// 	if (cmd->flag_end == APPEND_FILE
// 		|| cmd->flag_end == REPLACE_FILE)
// 		i += add_outfile_name(command + i);	
// 	if (i > 0)
// 	{
// 		cmd->to_do = ft_substr(command, 0, i - 1)
// 		if (!cmd->to_do)
// 			free_and_exit(MEMO);
// 	}
// 	return (i + 2);
// }

void	execute_command(char *command)
{
	t_command	cmd;

	cmd.flag_start = STDIN_FILENO;
	cmd.flag_end = STDOUT_FILENO;
	cmd.infile = 0;
	cmd.outfile = 1;
	signal(SIGINT, monitor_sigint);
	signal(SIGQUIT, SIG_DFL);
	while (*command)
	{
		//command += find_command(command, &cmd);
		//parse_command(cmd);
		dispatch_execute(&cmd);
		command++;
	}
	exit(EXIT_SUCCESS);
}
