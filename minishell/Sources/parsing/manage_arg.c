/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:30:56 by tonted            #+#    #+#             */
/*   Updated: 2022/11/09 10:54:24 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define RESET_FLAG 0x0
#define S_QUOTE 0x1
#define D_QUOTE 0x2

int	interpret_var(char **s, int i, char **envp)
{
	int		i_end;
	int		i_env;
	char	c_tmp;
	char	*tmp1;
	char	*tmp2;

	i_end = 1 + i;
	while (ft_isalnum((*s)[i_end]))
		i_end++;
	c_tmp = (*s)[i_end];
	(*s)[i_end] = '\0';
	i_env = is_name_in_envp(envp, &(*s)[i + 1]);
	if (i_env == -1)
		tmp1 = "";
	else
		tmp1 = get_value(envp[i_env]);
	(*s)[i] = '\0';
	tmp2 = ft_strjoin(*s, tmp1);
	(*s)[i_end] = c_tmp;
	tmp1 = ft_strjoin(tmp2, &(*s)[i_end]);
	i = ft_strlen(tmp2);
	free(tmp2);
	(*s) = tmp1;
	return (i);
}

int	interpret_status(t_cmd *cmd, char **envp, int i, int i_s)
{
	char	*tmp1;

	(void)envp;
	cmd->cmd[i][i_s] = '\0';
	tmp1 = ft_strjoin(cmd->cmd[i], ft_itoa(*last_status()));
	cmd->cmd[i] = ft_strjoin(tmp1, &cmd->cmd[i][i_s]);
	free_null(tmp1);
	return (EXIT_SUCCESS);
}

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
		{	
			if (cmd->cmd[i_cmd][i + 1] == '?')
				i = interpret_status(cmd, envp, i_cmd, i);
			else
				i = interpret_var(&cmd->cmd[i_cmd], i, envp);
		}
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
