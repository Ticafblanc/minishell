/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/10/13 16:41:30 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	manage_operators(char **command, t_cmd **cmd, int *nb_word, char **envp)
{
	(void) envp;
	if (**command == '\0')
		return (0);
	if (check_metacharacter(command, R_INVISIBLE))
		return (0);
	if ((command[0][0] == '|' && command[0][1] == '|')
		|| (command[0][0] == '&' && command[0][1] == '&'))
		return (parsing_and_or(command, cmd, nb_word));
	else if (**command == '|')
		return (parsing_pipe(command, cmd, nb_word));
	else
		command[0][1] = '\0';
	return (perror_minishell(TOKENERR, *command));
}

// TODO Que veux dire msltadd (maillon list add!)
// TODO voir pour faire un fonction! pour gerer les 20 d'allocation!
t_cmd	*ft_mlstadd(t_cmd *cmd, int *status)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new)
	{
		new->cmd = (char **)ft_calloc(20, sizeof(char *)); 
		if (new->cmd)
		{
			new->ctrl_op = END;
			new->status = 0;
			new->path = NULL;
			new->infile = STDIN_FILENO;
			new->outfile = STDOUT_FILENO;
			if (cmd)
				cmd->next = new;
			else
				new->next = NULL;
			return (new);
		}
		free(new);
	}
	*status = errno;
	perror("minishell:");
	return (NULL);
}
