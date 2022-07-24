/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/11 18:30:06 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	perror_minishell(int status, char *command)
{
	//printf("status ->%c\n", (char)status);
	if (status > 2)
	{
		if (status == NCMD)
			dprintf(2,"minishell: %s: command not found ", command);
		else if (status == 34 || status == 39)
			dprintf(2,"minishell: syntax error `%c' not close\n", (char)status);
		else 
			dprintf(2,"minishell: syntax error near unexpected token `%s'\n", command);
		return (status + 128);
	}
	return (status);
}

// static int	exec_cmd(t_cmd *cmd, int status)
// {
	
// 	int		status;

// 	if (cmd->ctrl_op == PIPE)
// 	{
// 		cmd->pid = fork;
// 		if (!cmd->pid)
// 			execve(cmd->cmd[0], cmd->cmd, g_envp);
// 		//interprete retour command pour || et && page 42 stau de sortie
// 										//voir gesion du sigpipe
// 	}
// 	else if (cmd->ctrl_op == AND)
// 	{
// 		if (cmd->bultin)
// 			exec_bultin(cmd->bultin);
// 		cmd->pid = fork;
// 		if (!cmd->pid)
// 			execve(cmd->cmd[0], cmd->cmd, g_envp);
// 		waitpid(cmd->pid, &cmd->status, 0);//interprete retour command pour || et && page 42 stau de sortie
// 										//voir gesion du sigpipe
// 	}
// 	else if (cmd->ctrl_op == OR)
// 	{
// 		if (cmd->bultin)
// 			exec_bultin(cmd->bultin);
// 		cmd->pid = fork;
// 		if (!cmd->pid)
// 			execve(cmd->cmd[0], cmd->cmd, g_envp);
// 		waitpid(cmd->pid, &cmd->status, 0);//interprete retour command pour || et && page 42 stau de sortie
// 										//voir gesion du sigpipe
// 	}
// }
static int	exec_cmd(t_cmd *cmd, int *status, char **envp)
{
	while (cmd)
	{
		while (*cmd->cmd && **envp)
		{
			printf("cmd->cmd = %s\n", *cmd->cmd);
			printf("infile = %d\n", cmd->infile);
			printf("outfile = %d\n\n", cmd->outfile);
			cmd->cmd++;
		}
		cmd = cmd->next;
	}
	return(*status);
}

static void	parsing(char *command, int *status, t_cmd **cmd)
{
	int		nb_word;
	int		trig;
	t_cmd	*t_cmd;

	nb_word = 0;
	trig = 0;
	*status = 0;
	(*cmd) = ft_mlstadd((*cmd), status);
	t_cmd = *cmd;
	while (!(*status) && *command != '\0')
	{
		//printf("pars ->%c\n", *command);
		if (check_metacharacter(*command))
		 	*status = parsing_met(&command, &t_cmd, &nb_word, &trig);
		else if (!trig)
			*status = add_word(&command, t_cmd, &nb_word, &trig);
		else
			command++;

	}
	return ;
}

static int	execute(char *command, int *status, char **envp)
{
	t_cmd	*cmd = NULL;

	*status = 0;
	add_history(command);
	parsing(command, status, &cmd);
	printf("2status ->%d\n", *status);
	if (!(*status))
	{
		while (cmd)
		{
			exec_cmd(cmd, status, envp);
			cmd = cmd->next;
		}
	}
	//wait_and_free(cmd);// voir si necessaire
	//free_cmd(cmd);
	return (*status);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	char	*command;
	
	status = 0;
	if (argc == 1)
	{
		while (argc)
		{
			signal(SIGINT, handle_prompt);
			signal(SIGQUIT, SIG_IGN);
			command = readline("minishell %");
			if (!command)
				exit(EXIT_SUCCESS);
			else if (command[0] != '\0')
				execute(command, &status, envp);
			else
				free(command);
		}
	}
	else if (argc > 1 && ft_strncmp(argv[1], "-c", 2) == 0)
		exit(execute(argv[2], &status, envp));// exit
	dprintf(2, "minshell: %s: invalid option\n"
	"Usage: minishell [option] [command]\n"
	"Shell option :\n\t-c command\n", argv[1]);
	exit(2);
}
