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

static int	exec_cd(char *dir, char ***envp)
{
	char	*str;
	int		i;

	i = 0;
	str = getcwd(NULL, 0);
	if (chdir(dir))
		return (perror_minishell(errno, "minishell:"));
	while (envp[0][i] && ft_strncmp(envp[0][i], "OLDPWD=", 7) != 0)
		i++;
	if(ft_strncmp(envp[0][i], "OLDPWD=", 7) == 0)
	{
		free(envp[0][i]);
		envp[0][i] = ft_strjoin("OLDPWD=", str);
		free(str);
	}
	i = 0;
	while (envp[0][i] && ft_strncmp(envp[0][i], "PWD=", 4) != 0)
		i++;
	if(ft_strncmp(envp[0][i], "PWD=", 4) == 0)
	{
		free(envp[0][i]);
		str = getcwd(NULL, 0);
		envp[0][i] = ft_strjoin("PWD=", str);
		free(str);
	}
	return (1);
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

int	exec_exit(int process, char ***envp)
{
	if (process == MAIN)
		printf("exit\n");
	ft_free_pp((void **)*envp);
	exit(EXIT_SUCCESS);
	return (0);
}

int	exec_builtins(t_cmd *cmd, int *status, char ***envp, int process)
{
	if (envp)

	if (status)

	// if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
	// 	return (exec_echo(cmd, status, envp));
	if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
		return (exec_cd(cmd->cmd[1], envp));
	if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0)
		return (exec_pwd());
	// else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
	// 	return (exec_export(cmd, status, envp));
	// else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
	// 	return (exec_unset(cmd, status, envp));
	if (ft_strncmp(cmd->cmd[0], "env", 3) == 0)
		return (exec_env(*envp));
	if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0)
		exec_exit(process, envp);
	return (0);
	
}