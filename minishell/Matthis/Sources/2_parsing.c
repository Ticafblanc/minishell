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

extern char	**g_envp;

static int	pass_quote(char *command, int *i, t_cmd *cmd)
{
	int		save_i;

	save_i = *i;
	if (ft_strncmp(command[*i], 34, 1) != 0 || ft_strncmp(command[*i], 39, 1) != 0)
		return (0);
	while(command[*i])
	{
		if (command[*i] == command[save_i])
		{
			*i++;
			return (0);
		}
	}
	free_and_error(QUOTE, cmd);
	return (-1);
}

static t_cmd	*ft_mlstadd(t_cmd *cmd)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
	{
		free_and_error(MEMO, cmd);
		return (new = NULL);
	}
	new->next = NULL;
	new->ctrl_op = 0;
	new->infile = READ_END;
	new->outfile = WRITE_END;
	if (!cmd)
		cmd = new;
	else
		cmd->next = new;
	return (new);
}

static int	tok_operator(char command, int *i, t_cmd **tmp_cmd)
{
	char	*str;
	char	quote;
	int		flag;

	flag = 0;
	if (command[i] == '|')
		flag = parsing_pipe(command, i, tmp_cmd);
	else if (command[i] == '&' || command[i] == '\n')
		flag = parsing_and(command, i, tmp_cmd);
	// else if (command[i] == '(' || command[i] == ')')
	// 	flag = parsing_brace(command, i, tmp_cmd);
	else if (command[i] == '<')
		flag = parsing_infile(command, i, tmp_cmd);
	else if (command[i] == '>')
		flag = parsing_outfile(command, i, tmp_cmd);
	else
	{
		*i++;
		return (0);
	}
	if (!(*tmp_cmd = ft_mlstadd(*tmp_cmd)))
		return (-1);
	return (flag);
}

int	parsing_last (char *command, t_cmd *cmd)
{
	int	i;

	i = 0;
	ft_strtok(command, '\0');
	while (command[i])
	{
		while (check_invisible_characters(command[i]))
			i++;
		while (!check_invisible_characters(command[i]))
			i++;
		
	}
}

int	parsing_tok(char *command, t_cmd **cmd)
{
	t_cmd	*tmp_cmd;
	int		i;

	i = 0;
	ft_strtok(command, '\0');
	if (!(tmp_cmd = ft_mlstadd(*cmd)))
		return (-1);
	while (command[i])
	{
		if (pass_quote(command, &i, cmd))
			return (-1); 
		if (tok_operator(command, &i, &tmp_cmd))
			return (-1);
	}
	if (parsing_last(ft_strtok(command, '\0'), tmp_cmd))
		return (-1);
	return (0);
}
