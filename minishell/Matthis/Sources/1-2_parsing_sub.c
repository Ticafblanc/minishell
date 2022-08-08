/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-2_parsing_sub.c                                  :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parsing_and_or(char **command, t_cmd **cmd, int *nb_word)
{
	int		status;

	if (**(*cmd)->cmd != **command)
	{
		(*cmd)->cmd[(*nb_word)] = NULL;
		if (command[0][0] == '&')
			(*cmd)->ctrl_op = AND;
		else
			(*cmd)->ctrl_op = OR;
		status = 0;
		check_metacharacter(command, R_METACHARACTER);
		check_metacharacter(command, R_METACHARACTER);
		if (!ft_str_len((*cmd)->cmd[--(*nb_word)]))
			(*cmd)->cmd[(*nb_word)] = NULL;
		(*cmd) = ft_mlstadd((*cmd), &status);
		(*nb_word) = 0;
		return(0);
	}
	command[0][2] = '\0';
	return (perror_minishell(TOKENERR, *command));
}

int	parsing_pipe(char **command, t_cmd **cmd, int *nb_word, char **envp)
{
	int		status;
	int		i;

	i = 0;
	if (**(*cmd)->cmd != **command)
	{
		status = 0;
		(*cmd)->ctrl_op = PIPE;
		check_metacharacter(command, R_METACHARACTER);
		while (envp[i] && ft_strnstr(envp[i], "SUB=", 4) == 0)
			i++;
		(*cmd)->cmd[2] = ft_rev_split((const char **)(*cmd)->cmd, 32);
		(*cmd)->cmd[0] = envp[i] + 4;
		(*cmd)->cmd[1] = ft_strdup("-c");
		(*cmd)->cmd[3] = NULL;
		(*cmd)->path = ft_strdup("./Bin/minishell");
		(*cmd) = ft_mlstadd((*cmd), &status);
		(*nb_word) = 0;
		return(0);
	}
	command[0][1] = '\0';
	return (perror_minishell(TOKENERR, *command));
}

// int	parsing_brace(char **command, t_cmd **cmd, int *nb_word)
// {
// 	int		status;
// 	int		i;
// 	char	c;
// 	char	*temp;

// 	i = 0;
// 	int		nb_word;
// 	t_cmd	*t_cmd
// 	nb_word = 0;
// 	t_cmd = (*cmd) = ft_mlstadd((*cmd), status);
// 	t_cmd = *cmd;
// 	while (!(*status) && *command != '\0')
// 	{
// 		t_cmd->cmd[nb_word++] = find_next_word(&command, status);
// 		if (*command != '\0' && !parsing_redir(&command, t_cmd, status) && !(*status))
// 			*status = parsing_ctrl_op(&command, &t_cmd, &nb_word);
// 	}
// 	if (!(*cmd)->cmd[0])
// 	{
// 		status = 0;
// 		(*cmd)->ctrl_op = BRACE;
// 		i++;
// 		(*cmd)->cmd[0] = ft_strdup("minishell");
// 		(*cmd)->cmd[1] = ft_strdup("-c");
// 		(*cmd)->cmd[2] = *command;
// 		(*cmd)->cmd[3] = NULL;
// 		while (*command != '\0' && i > 0)
// 		{
// 			c = find_next_word(command, &temp)
// 			if (!check_metacharacter(*temp))

// 			else if (c == '(')
// 				i++;
// 			else if (c == ')')
// 				i--;
// 			if (i == 0)
// 				**command = '\0';
// 		}
// 		(*cmd)->path = ft_strdup("/Bin/minishell");
// 		(*cmd) = ft_mlstadd((*cmd), &status);
// 		(*nb_word) = 0;
// 		return(0);
// 	}
// 	*command++;
// 	while (command[0][i] != '\0' && check_invisible_characters(command[0][i]))
// 		i++;
// 	while (command[0][i] != '\0' && !check_metacharacter(command[0][i]))
// 		i++;
// 	command[0][i] == '\0'
// 	return (130);