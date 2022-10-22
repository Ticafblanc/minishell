/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_execute.c                                        :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// static void	wait_and_free(t_cmd *cmd)//voir gestion du sigpipe pour ficheir sans and of file
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





// //https://www.cyberciti.biz/faq/linux-bash-exit-status-set-exit-statusin-bash/
// //https://www.thegeekstuff.com/2010/10/linux-error-codes/



