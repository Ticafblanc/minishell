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

int	parsing_pipe(char **command, t_cmd **cmd, int *nb_word, int *trig)
{
	char	*temp;
	int		status;

	status = 0;
	parsing_invisible_characters(command, trig);
	(*cmd)->ctrl_op = PIPE;
	temp = ft_rev_split((const char **)(*cmd)->cmd, 32);
	printf("temp = %s\n", temp);
	// ft_free_pp((void **)(*cmd)->cmd + 4);
	// free((*cmd)->cmd[0]);
	// (*cmd)->cmd[0] = ft_strdup("minishell");
	// free((*cmd)->cmd[1]);
	// (*cmd)->cmd[1] = ft_strdup("-c");
	// free((*cmd)->cmd[2]);
	// (*cmd)->cmd[2] = temp;
	// free((*cmd)->cmd[3]);
	// (*cmd)->cmd[3] = NULL;
	// (*cmd)->path = ft_strdup("/Bin/minishell");
	(*cmd) = ft_mlstadd((*cmd), &status);
	(*nb_word) = 0;
	(*trig) = 0;
	return (status);
}