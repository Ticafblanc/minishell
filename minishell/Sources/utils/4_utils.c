/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/10/13 18:14:51 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
//voir gestion du sigpipe pour ficheir sans and of file
// static void	wait_and_free(t_cmd *cmd)
// {
// 	t_cmd	*tmp;

// 	tmp = cmd;
// 	while (cmd)
// 	{
// 		tmp = cmd->next;
// 		waitpid(-1, &cmd->status, 0);//waitpid(cmd->pid, &cmd->status, 0);
// 		if (cmd->cmd)
// 			ft_free_pp((void **)cmd->cmd);
// 		if (cmd->path)
// 			free(cmd->path);
// 		if (cmd->outfile != 1)
// 			close(cmd->outfile);
// 		if (cmd->infile != 0)
// 			close(cmd->infile);
// 		free(cmd);
// 		cmd = tmp;
// 	}
// }

// static int	exec_last(t_cmd *cmd, int status)
// {

// 	if (cmd->bultin)
// 		return (exec_bultin(cmd->bultin));
// 	if (status == SUB)
// 	{
// 		if (execve(cmd->path, cmd->cmd, g_envp))
// 			free_and_exit (EXIT_FAILURE);//gestion du retour erreur aimprimer
// 	}
// 	cmd->pid = fork;
// 	if (!cmd->pid)
// 		if (execve(cmd->path, cmd->cmd, g_envp))
// 			//gestion du retour d'erreur;
// 	return (0);
// }

// https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/
// https://www.thegeekstuff.com/2010/10/linux-error-codes/
*/

int	perror_minishell(int status, char *command)
{
	if (status == errno)
	{
		dprintf (2, "minishell: %s: %s \n", command, strerror(errno));
		status = 1;
	}
	else if (status == NCMD)
		dprintf (2, "minishell: %s: command not found\n", command);
	else if (status == QNC)
		dprintf (2, "minishell: syntax error `%c' not close\n", *command);
	else if (status == TOKENERR)
	{
		dprintf (2, "minishell: syntax error near unexpected token `%s'\n",
			command);
	}
	return (status);
}

void	wait_cmd(t_cmd *cmd, int *status, int ctrl_op)
{
	if (ctrl_op == PIPE)
	{
		while (cmd->ctrl_op == PIPE)
		{
			waitpid(cmd->pid, status, 0);
			cmd = cmd->next;
		}
		waitpid(cmd->pid, status, 0);
	}
	else if (ctrl_op == HERE_DOC)
	{
		while (cmd)
		{
			waitpid(cmd->pid, status, 0);
			cmd = cmd->next;
		}
	}
}

void	handle_prompt(int sig_num)
{
	if (sig_num == SIGINT)
	{		
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	handle_exec(int sig_num)
{
	if (sig_num == SIGINT)
		exit(EXIT_FAILURE);
}
