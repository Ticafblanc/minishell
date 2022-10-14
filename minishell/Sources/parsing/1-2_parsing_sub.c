/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-2_parsing_sub.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/10/14 02:19:34 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	int		i;

	i = 0;

	check_metacharacter(command, R_METACHARACTER);
	while (envp[i] && ft_strnstr(envp[i], "SUB=", 4) == 0)
		i++;
	if (ft_strnstr(envp[i], "SUB=", 4))
		return (perror_minishell(TOKENERR, *command));

	(*cmd)->cmd[3] = NULL;
	(*cmd)->path = ft_strdup("minishell");
*/

// TODO manage brace!

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
// 		if (*command != '\0' && !manage_redir(&command, t_cmd, status) 
//			&& !(*status))
// 			*status = manage_operators(&command, &t_cmd, &nb_word);
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