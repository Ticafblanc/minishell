/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:30:56 by tonted            #+#    #+#             */
/*   Updated: 2022/11/11 00:43:02 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define RESET_FLAG 0x0
#define S_QUOTE 0x1
#define D_QUOTE 0x2

bool	is_quote_closed(char f, char c)
{
	return (((c == '\'' && f == S_QUOTE) || (c == '\"' && f == D_QUOTE)));
}

void	shift_str(char **s, int i, char *flag, char flag_set)
{
	while ((*s)[i])
	{
		(*s)[i] = (*s)[i + 1];
		i++;
	}
	*flag = flag_set;
}

void	manage_arg(t_cmd *cmd, char **envp, int i_cmd)
{
	int		i;
	char	flag;

	i = 0;
	flag = RESET_FLAG;
	while (cmd->cmd[i_cmd][i] != '\0')
	{
		if (cmd->cmd[i_cmd][i] == '\"' && !flag)
			shift_str(&cmd->cmd[i_cmd], i, &flag, D_QUOTE);
		else if (cmd->cmd[i_cmd][i] == '\'' && !flag)
			shift_str(&cmd->cmd[i_cmd], i, &flag, S_QUOTE);
		else if (is_quote_closed(flag, cmd->cmd[i_cmd][i]))
			shift_str(&cmd->cmd[i_cmd], i, &flag, RESET_FLAG);
		else if (cmd->cmd[i_cmd][i] == '$' && flag != S_QUOTE)
			interpret_vars(cmd, i, i_cmd, envp);
		else if (cmd->cmd[i_cmd][i] == '*' && !cmd->cmd[i_cmd][i + 1])
			search_files(cmd, i_cmd);
		else
			i++;
	}
}

void	manage_args(t_cmd *cmd, char **envp)
{
	int	i_cmd;

	i_cmd = 0;
	while (cmd->cmd[i_cmd])
	{
		manage_arg(cmd, envp, i_cmd);
		i_cmd++;
	}
}