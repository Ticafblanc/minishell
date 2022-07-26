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

// int	parsing_and_or(char **command, t_cmd **cmd, int *nb_word, int *trig)
// {
// 	int		status;

// 	if ((*cmd)->cmd && (*cmd)->cmd[0])
// 	{
// 		if (command[0][0] == '&')
// 			(*cmd)->ctrl_op = AND;
// 		else
// 			(*cmd)->ctrl_op = OR;
// 		status = 0;
// 		parsing_invisible_characters(command, trig);
// 		parsing_invisible_characters(command, trig);
// 		(*cmd) = ft_mlstadd((*cmd), &status);
// 		(*nb_word) = 0;
// 		return(0);
// 	}
// 	command[0][1] = '\0';
// 	return (130);
// }

// int	parsing_pipe(char **command, t_cmd **cmd, int *nb_word, int *trig)
// {
// 	char	*temp;
// 	int		status;

// 	if ((*cmd)->cmd && (*cmd)->cmd[0])
// 	{
// 		status = 0;
// 		(*cmd)->ctrl_op = PIPE;
// 		parsing_invisible_characters(command, trig);
// 		temp = ft_rev_split((const char **)(*cmd)->cmd, 32);
// 		(*cmd)->cmd[0] = ft_strdup("minishell");
// 		(*cmd)->cmd[1] = ft_strdup("-c");
// 		(*cmd)->cmd[2] = temp;
// 		(*cmd)->cmd[3] = NULL;
// 		(*cmd)->path = ft_strdup("/Bin/minishell");
// 		(*cmd) = ft_mlstadd((*cmd), &status);
// 		(*nb_word) = 0;
// 		return(0);
// 	}
// 	command[0][1] = '\0';
// 	return (130);
// }

// // int	parsing_brace(char **command, t_cmd **cmd, int *nb_word, int *trig)
// // {
// // 	int		status;
// // 	int		i;
// // 	char	c;
// // 	char	*temp;

// // 	i = 0;
// // 	if (!(*cmd)->cmd[0])
// // 	{
// // 		status = 0;
// // 		(*cmd)->ctrl_op = BRACE;
// // 		i++;
// // 		parsing_invisible_characters(command, trig);
// // 		(*cmd)->cmd[0] = ft_strdup("minishell");
// // 		(*cmd)->cmd[1] = ft_strdup("-c");
// // 		(*cmd)->cmd[2] = *command;
// // 		(*cmd)->cmd[3] = NULL;
// // 		while (*command != '\0' && i > 0)
// // 		{
// // 			c = find_next_word(command, &temp)
// // 			if (!check_metacharacter(*temp))

// // 			else if (c == '(')
// // 				i++;
// // 			else if (c == ')')
// // 				i--;
// // 			if (i == 0)
// // 				**command = '\0';
// // 		}
// // 		(*cmd)->path = ft_strdup("/Bin/minishell");
// // 		(*cmd) = ft_mlstadd((*cmd), &status);
// // 		(*nb_word) = 0;
// // 		return(0);
// // 	}
// // 	*command++;
// // 	while (command[0][i] != '\0' && check_invisible_characters(command[0][i]))
// // 		i++;
// // 	while (command[0][i] != '\0' && !check_metacharacter(command[0][i]))
// // 		i++;
// // 	command[0][i] == '\0'
// // 	return (130);