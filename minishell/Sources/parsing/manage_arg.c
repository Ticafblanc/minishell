/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:30:56 by tonted            #+#    #+#             */
/*   Updated: 2022/11/09 09:34:11 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define RESET_FLAG 0x0
#define S_QUOTE 0x1
#define D_QUOTE 0x2
void	search_files(t_cmd *cmd, int i);

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

bool	is_quote_closed(char f, char c, int *count)
{
	return (((c == '\'' && f == S_QUOTE) || (c == '\"' && f == D_QUOTE))
				&& ++(*count));
}
void	shift_str(char **s, int i)
{
	while (s[i])
	{
		s[i] = s[i + 1];
		i++;
	}
}

void	manage_arg(t_cmd *cmd, char **envp, int i_cmd)
{
	int		i;
	int		count;
	char	flag;

	count = 0;
	i = 0;
	flag = RESET_FLAG;
	while (cmd->cmd[i_cmd][i] != '\0')
	{
		if (cmd->cmd[i_cmd][i] == '\"' && !flag && ++count)
		{
			flag = D_QUOTE;
			if (cmd->cmd[i_cmd][i + 1] == '$')
			{
				cmd->cmd[i_cmd][i++] = '\0';
				i = interpret_var(&cmd->cmd[i_cmd], i, envp);
				count = 0;
				continue;
			}
		}
		else if (cmd->cmd[i_cmd][i] == '\'' && !flag && ++count)
			flag = S_QUOTE;
		else if (is_quote_closed(flag, cmd->cmd[i_cmd][i], &count))
		{
			flag = RESET_FLAG;
			if (count == 2)
				--i;
			int j = i;
			while(cmd->cmd[i_cmd][j])
			{
				cmd->cmd[i_cmd][j] = cmd->cmd[i_cmd][j + count];
				j++;
			}
			count = 0;
			continue;
		}	
		else if (cmd->cmd[i_cmd][i] == '$' && flag != S_QUOTE)
		{
			i = interpret_var(&cmd->cmd[i_cmd], i, envp);
			count = 0;
			continue ;
		}
		else if (cmd->cmd[i_cmd][i] == '*' && !cmd->cmd[i_cmd][i + 1])
			search_files(cmd, i_cmd);
		cmd->cmd[i_cmd][i] = cmd->cmd[i_cmd][i + count];
		i++;
	}
	cmd->cmd[i_cmd][i - count] = '\0';
}

void	manage_args(t_cmd *cmd, char **envp)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		manage_arg(cmd, envp, i);
		i++;
	}
}