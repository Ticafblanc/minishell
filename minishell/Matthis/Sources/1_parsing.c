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

static t_cmd	*ft_mlstnew()
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (cmd = NULL);
	cmd->next = cmd;
	return (cmd);
}

static t_cmd	ft_mlstadd(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*l_cmd;

	if (!new)
		return (new);
	if (!*cmd)
	{
		*cmd = new;
		return (*cmd);
	}
	else
	{
		l_cmd = ft_lstlast(*cmd);
		l_cmd->next = new;
		return (new);
	}
}

void	parsing(char *command)
{
	t_cmd	*cmd;
	t_cmd	*tmp;
	int		i;

	while (*command)
	{
		if (!(tmp = ft_mlstadd(&cmd, ft_mlstnew())))
			free_and_error(MEMO, cmd);
		while (!ft_find_control_operator(*command, cmd))
		{
			ft_find_metacharacter(&command, cmd);

		}
	}
}
