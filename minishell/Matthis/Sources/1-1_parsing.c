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

int	pass_quote(char **command, t_cmd *cmd, char c)
{
    cmd->
	while(**command != '\0')
	{
		if (**command == c)
		{
			*command++;
			return (EXIT_SUCCESS);
		}
	}
	perror("bash : quote not close");
	return (c);
}


// int	parsing_file(&command, cmd, &nb_word, &trig)
// {

// }

// int	parsing_op(&command, &cmd, &nb_word, &trig)
// {

// }

// void	parsing_invisble(char **command, int *trig)
// {
// 	if (*trig == 1)
// 	{
// 		**command = '\0';
// 		trig = 0;
// 	}				
// 	*command++;
// }

// int	add_word(char **command, t_cmd *cmd, int *nb_word, int *trig)
// {
// 	char **tmp_cmd;

// 	if (*trig == 0)
// 	{
// 		if (cmd->cmd)
// 		{
// 			tmp_cmd = cmd->cmd;
// 			cmd->cmd = (char **)ft_calloc(*nb_word + 2, sizeof(char *));
// 			if (!cmd->cmd)
// 				{
// 					perror("bash :");
// 					return (EXIT_FAILURE);
// 				}
// 			while (tmp_cmd)
// 			{
// 				*cmd->cmd = *tmp_cmd;
// 				cmd->cmd++;
// 				tmp_cmd++;
// 			}
// 			*cmd->cmd = **command;
// 		*nb_word++;
// 		}
// 	}
// 	return(0);
// }

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
		*status = errno;
		free(new);
		return (new = NULL);
	}
	*status = errno;
	return (new = NULL);
}
