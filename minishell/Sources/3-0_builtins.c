/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_builtins.c                                       :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exec_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
	free(buf);
	return (1);
}

static int	exec_cd2(char **str, char ***envp)
{
	int		i;

	i = 0;
	while (envp[0][i] && ft_strncmp(envp[0][i], "OLDPWD=", 7) != 0)// gestion de staut pour retour 
		i++;
	if(ft_strncmp(envp[0][i], "OLDPWD=", 7) == 0)
	{
		free(envp[0][i]);
		envp[0][i] = ft_strjoin("OLDPWD=", *str);
		free(*str);
	}
	i = 0;
	while (envp[0][i] && ft_strncmp(envp[0][i], "PWD=", 4) != 0)
		i++;
	if(ft_strncmp(envp[0][i], "PWD=", 4) == 0)
	{
		free(envp[0][i]);
		*str = getcwd(NULL, 0);
		envp[0][i] = ft_strjoin("PWD=", *str);
		free(*str);
	}
	return (1);
}

static int	exec_cd(char *dir, char ***envp)
{
	char	*str;
	int		i;

	i = 0;
	if (!dir)
	{
		while (envp[0][i] && ft_strncmp(envp[0][i], "HOME=", 5) != 0)
			i++;
		dir = envp[0][i] + 5;
		i = 0;
	}
	str = getcwd(NULL, 0);
	if (chdir(dir))
		return (perror_minishell(errno, "minishell:"));
	return (exec_cd2(&str, envp));
}

static int	exec_env(char **envp)
{
	while(*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (1);
}

int	exec_builtins1(t_cmd *cmd, int *status, char ***envp, int process)
{
	int	i;

	i = 0;
	if (!ft_strncmp(cmd->cmd[0], "cd", 2))
		return (exec_cd(cmd->cmd[1], envp));
	if (!ft_strncmp(cmd->cmd[0], "pwd", 3))
		return (exec_pwd());
	if (!ft_strncmp(cmd->cmd[0], "env", 3))
		return (exec_env(*envp));
	else
		i = exec_builtins2(cmd, status, envp, process);
	return (i);
	
}