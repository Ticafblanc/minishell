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
	int i;
	int i2;

	i = 0;
	while (cmd)
	{
		i2 = 0;
		while (*cmd->cmd && **envp)
		{
			printf("\ncmd = %d\n", i);
			printf("cmd->cmd[%d] = %s\n", i2, *cmd->cmd);
			printf("infile = %d\n", cmd->infile);
			printf("outfile = %d\n\n", cmd->outfile);
			cmd->cmd++;
			i2++;
		}
		i++;
		cmd = cmd->next;
	}
	return(*status);
}

static void	parsing(char *command, int *status, t_cmd **cmd)
{
	int		nb_word;
	t_cmd	*t_cmd;

	nb_word = 0;
	(*cmd) = ft_mlstadd((*cmd), status);
	//printf("status in parsing = %d\n", *status);
	t_cmd = *cmd;
	while (!(*status) && *command != '\0')
	{
		while (check_metacharacter(&command, R_INVISIBLE))
		(*cmd)->cmd[nb_word++] = command;
		while (!pass_quote(&command, status) && *command != '\0'
				&& !check_metacharacter(&command, N_METACHARACTER))
		// if ((*command == '<' && *command == *command + 1))
		// 	*status = parsing_redir(&command, *cmd, HERE_DOC);
		// else if ((*command == '>' && *command == *command + 1))
		// 	*status = parsing_redir(&command, *cmd, APPEND);
		// else if (*command == '<')
		// 	*status = parsing_redir(&command, *cmd, INFILE);
		// else if (*command == '>')
		// 	*status = parsing_redir(&command, *cmd, OUTFILE);
		if (!(*status) && *command != '\0')
			*status = parsing_ctrl_op(&command, &t_cmd, &nb_word);
	}
}

static int	execute(char *command, int *status, char **envp)
{
	t_cmd	*cmd = NULL;

	add_history(command);
	*status = 0;
	parsing(command, status, &cmd);
	//printf("status de sortie de parsing ->%d\n", *status);
	if (*status == 0)
	{
		//printf("status de sortie de parsing@ ->%d\n", *status);
		//printf("cmd -> %s\n", cmd->cmd[0]);
		while (cmd)
		{
			exec_cmd(cmd, status, envp);
			//printf("status de sortie de command ->%d\n", *status);
		}
	}
	free_cmd(cmd);
	//wait et free a gere
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
		exit(execute(argv[2], &status, envp));
	dprintf(2, "minshell: %s: invalid option\n"
	"Usage: minishell [option] [command]\n"
	"Shell option :\n\t-c command\n", argv[1]);
	exit(2);
}








//printf("cmd -> %s\n", t_cmd->cmd[nb_word]);
		// if (check_metacharacter(*command))
		//  	*status = parsing_met(&command, &t_cmd, &nb_word, &trig);
		// else if (!trig || *command == 34 || *command == 39)
		// 	*status = add_word(&command, t_cmd, &nb_word, &trig);
		// else
		// 	command++;