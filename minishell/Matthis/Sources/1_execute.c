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

extern char	**g_envp;

static void	wait_and_free(t_cmd *cmd)//voir gestion du sigpipe pour ficheir sans and of file
{
	t_cmd	*tmp;

	tmp = cmd;
	while (cmd)
	{
		tmp = cmd->next;
		waitpid(-1, &cmd->status, 0);//waitpid(cmd->pid, &cmd->status, 0);
		if (cmd->cmd)
			ft_free_pp((void **)cmd->cmd);
		if (cmd->path)
			free(cmd->path);
		if (cmd->outfile != 1)
			close(cmd->outfile);
		if (cmd->infile != 0)
			close(cmd->infile);
		free(cmd);
		cmd = tmp;
	}
}

static int	exec_last(t_cmd *cmd, int status)
{
	
	if (cmd->bultin)
		return (exec_bultin(cmd->bultin));
	if (status == SUB)
	{
		if (execve(cmd->path, cmd->cmd, g_envp))
			free_and_exit (EXIT_FAILURE);//gestion du retour erreur aimprimer
	}
	cmd->pid = fork;
	if (!cmd->pid)
		if (execve(cmd->path, cmd->cmd, g_envp))
			//gestion du retour d'erreur;
	return (0);
}

static int	exec_sub(t_cmd *cmd, int status)
{
	
	int		status;

	if (cmd->ctrl_op == PIPE)
	{
		cmd->pid = fork;
		if (!cmd->pid)
			execve(cmd->cmd[0], cmd->cmd, g_envp);
		//interprete retour command pour || et && page 42 stau de sortie
										//voir gesion du sigpipe
	}
	else if (cmd->ctrl_op == AND)
	{
		if (cmd->bultin)
			exec_bultin(cmd->bultin);
		cmd->pid = fork;
		if (!cmd->pid)
			execve(cmd->cmd[0], cmd->cmd, g_envp);
		waitpid(cmd->pid, &cmd->status, 0);//interprete retour command pour || et && page 42 stau de sortie
										//voir gesion du sigpipe
	}
	else if (cmd->ctrl_op == OR)
	{
		if (cmd->bultin)
			exec_bultin(cmd->bultin);
		cmd->pid = fork;
		if (!cmd->pid)
			execve(cmd->cmd[0], cmd->cmd, g_envp);
		waitpid(cmd->pid, &cmd->status, 0);//interprete retour command pour || et && page 42 stau de sortie
										//voir gesion du sigpipe
	}
}

static int	parsing(char *command, t_cmd *cmd, int *status)
{
	int	nb_word;
	int	trig;

	nb_word = 0;
	trig = 0;
	while (*command != '\0')
	{
		if (*command == 34 || *command == 39)
			*status = pass_quote(&command, cmd, *command);
		else if (*command == '|' || *command == '&' || *command == '(' || *command == ')')
			*status = parsing_op(&command, &cmd, &nb_word, &trig);
		else if (*command == '<' || *command == '>')
			*status = parsing_file(&command, cmd, &nb_word, &trig);
		else if (check_invisible_characters(*command))
			parsing_invisble(&command, &trig);
		else
			*status = add_word(&command, cmd, &nb_word, &trig);
		if (*status)
			return (-1);
	}
	return (0);
}

int	execute(char *command, int *status)
{
	t_cmd	*cmd;

	if (!(cmd = ft_mlstadd(*cmd)))
		return (-1);
	if (parsing(command, cmd, status))
	{
		free_cmd(cmd);
		return (status);
	}
	while (cmd->next != NULL)
	{
		status = exec_sub(cmd, status);//prevoir gestion des et et des ou
		cmd = cmd->next;
	}
	status = exec_last(cmd, status);
	wait_and_free(cmd);
	return (status);
}

