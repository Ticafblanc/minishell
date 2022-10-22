/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
<<<<<<< HEAD:minishell/Matthis/Sources/main.c
/*   main.c                                             :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
=======
/*   ft_hexlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
>>>>>>> origin/ours🧸:libft/Sources/ft_hexlen.c
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:23:47 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/02/01 09:50:34 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

<<<<<<< HEAD:minishell/Matthis/Sources/main.c
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
=======
int	ft_hexlen(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 16;
		len++;
	}
	return (len);
>>>>>>> origin/ours🧸:libft/Sources/ft_hexlen.c
}

static void	parsing(char *command, int *status, t_cmd **cmd)
{
	int		nb_word;
	t_cmd	*t_cmd;

	nb_word = 0;
	t_cmd = (*cmd) = ft_mlstadd((*cmd), status);
	//printf("status in parsing = %d\n", *status);
	t_cmd = *cmd;
	while (!(*status) && *command != '\0')
	{
		while (check_metacharacter(&command, R_INVISIBLE));
		t_cmd->cmd[nb_word++] = command;
		while (*command != '\0' && !pass_quote(&command, status)
			&& !check_metacharacter(&command, METACHARACTER));	
		if (*command != '\0' && !parsing_redir(command, *cmd, status) && !(*status))
			*status = parsing_ctrl_op(&command, &t_cmd, &nb_word);
	}
}

static int	execute(char *command, int *status, char **envp)
{
	t_cmd	*cmd = NULL;

	add_history(command);
	*status = 0;
	parsing(command, status, &cmd);
	printf("status de sortie de parsing ->%d\n", *status);
	if (*status == 0)
	{
		//printf("status de sortie de parsing@ ->%d\n", *status);
		//printf("cmd -> %s\n", cmd->cmd[0]);
		while (cmd)
		{
			exec_cmd(cmd, status, envp);
			cmd = cmd->next;
			printf("status de sortie de command ->%d\n", *status);
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