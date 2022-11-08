/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_argv2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:30:56 by tonted            #+#    #+#             */
/*   Updated: 2022/11/08 21:47:03 by tonted           ###   ########.fr       */
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

int	interpret_varv2(char **s, int i, char **envp)
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

// 012345678901234567890123
// "Hello World"$ted*"ahah"
// 
// 0123456789
// "Hello"blabla
// Hellob"b
// "Hello"
// Hello""
int	manage_d_quote(char **arg, int i, char **envp)
{
	int		ret;
	int		i_tmp;

	i_tmp = i;
	(*arg)[i] = (*arg)[i + 1];
	while ((*arg)[++i] != '\"')
	{
		(*arg)[i] = (*arg)[i + 1];
	}
	(*arg)[i] = (*arg)[i + 2];
	ret = --i;
	while ((*arg)[i])
	{
		(*arg)[i] = (*arg) [i + 2];
		i++;
	}
	i = i_tmp;
	while (i <= ret)
	{
		if ((*arg)[i] == '$')
			ret = interpret_varv2(arg, i, envp);
		i++;
	}
	return (ret);
}

int	manage_s_quote(char *arg, int i)
{
	int		ret;

	arg[i] = arg[i + 1];
	while (arg[++i] != '\"')
		arg[i] = arg[i + 1];
	arg[i] = arg[i + 2];
	ret = --i;
	while (arg[i])
	{
		arg[i] = arg [i + 2];
		i++;
	}
	return (ret);
}

void	search_files(t_cmd *cmd, int i);

void	manage_argv2(char **envp, t_cmd *cmd, int i_cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i_cmd] && cmd->cmd[i_cmd][i])
	{
		if (cmd->cmd[i_cmd][i] == '\"')
			i = manage_d_quote(&cmd->cmd[i_cmd], i, envp) - 1;
		else if (cmd->cmd[i_cmd][i] == '\'')
			i = manage_s_quote(cmd->cmd[i_cmd], i) - 1;
		else if (cmd->cmd[i_cmd][i] == '$')
			i = interpret_varv2(&cmd->cmd[i_cmd], i , envp) - 1;
		else if (cmd->cmd[i_cmd][i] == '*' && cmd->cmd[i_cmd][i + 1] == '\0')
		{
			search_files(cmd, i_cmd);
			break;
		}
		else
			i++;
	}
}

void	manage_argsv2(t_cmd *cmd, char **envp)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		manage_argv2(envp, cmd, i);
		i++;
	}
}