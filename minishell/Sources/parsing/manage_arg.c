/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:30:56 by tonted            #+#    #+#             */
/*   Updated: 2022/11/08 21:39:29 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * 
 * interpreter VAR
 * interpreter *
 * remove quote 
 * 
 */

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

	//search end of name
	i_end = 1 + i;
	while (ft_isalnum((*s)[i_end]))
		i_end++;

	//keep char after end name
	c_tmp = (*s)[i_end];

	//split name to string
	(*s)[i_end] = '\0';

	//get the value in envp if exists
	i_env = is_name_in_envp(envp, &(*s)[i + 1]);
	if (i_env == -1)
		tmp1 = "";
	else
		tmp1 = get_value(envp[i_env]);

	//replace $ by `\0`
	(*s)[i] = '\0';

	//concat begin string to value
	tmp2 = ft_strjoin(*s, tmp1);

	// put back char after end word
	(*s)[i_end] = c_tmp;

	//join new s with next
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

void	search_files(t_cmd *cmd, int i);


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
		printf(">> i: %d HERE >%s< count: %d\n",i ,cmd->cmd[i_cmd], count);
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
			printf("#1=> i: %d HERE >%s< count: %d\n",i ,cmd->cmd[i_cmd], count);
			cmd->cmd[i_cmd][i] = cmd->cmd[i_cmd][i + count];
			printf("#2=> i: %d HERE >%s< count: %d\n",i ,cmd->cmd[i_cmd], count);
			i -= count;
			int j = i;
			while(cmd->cmd[i_cmd][j])
			{
				cmd->cmd[i_cmd][j] = cmd->cmd[i_cmd][j + count];
				j++;
			}
			count = 0;
			// --i;
			printf("#3=> i: %d HERE >%s< count: %d\n",i ,cmd->cmd[i_cmd], count);
		}	
		else if (cmd->cmd[i_cmd][i] == '$' && flag != S_QUOTE)
		{
			// printf("=> i: %d HERE >%s< count: %d\n",i ,cmd->cmd[i_cmd], count);
			i = interpret_var(&cmd->cmd[i_cmd], i, envp);
			count = 0;
			continue ;
		}
		else if (cmd->cmd[i_cmd][i] == '*' && !cmd->cmd[i_cmd][i + 1])
			search_files(cmd, i_cmd);
		cmd->cmd[i_cmd][i] = cmd->cmd[i_cmd][i + count];
		printf("<< i: %d HERE >%s< count: %d\n",i ,cmd->cmd[i_cmd], count);
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