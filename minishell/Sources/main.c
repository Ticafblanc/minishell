/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/09/26 17:39:27 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	child_process(int fd[2])
{
	char	*str;

	signal(SIGINT, handle_exec);
	close(fd[STDIN_FILENO]);
	str = readline("> ");
	while (!str || !*str)
	{
		if (!str)
			exit(perror_minishell(TOKENERR, "end of file"));
		str = readline("> ");
	}
	ft_putstr_fd(str, fd[STDOUT_FILENO]);
	free(str);
	close(fd[STDOUT_FILENO]);
	exit(EXIT_SUCCESS);
}

static int	check_command(char **command, int *status)
{
	char	*str;
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (perror_minishell(errno, "Fork child_process"));
	pid = fork();
	if (pid == -1)
		return (perror_minishell(errno, "Fork child_process"));
	if (!pid)
		child_process(fd);
	close(fd[STDOUT_FILENO]);
	waitpid(pid, status, 0);
	if (!*status)
	{
		str = get_next_line(fd[STDIN_FILENO]);
		*command = str;
	}
	close(fd[STDIN_FILENO]);
	return (*status);
}

static t_cmd	*parsing(char *command, int *status, t_cmd **cmd, char **envp)
{
	int		nb_word;
	t_cmd	*t_cmd;
	char	*save;
	char	*temp;

	save = ft_strdup(command);
	nb_word = 0;
	*cmd = ft_mlstadd((*cmd), status);
	t_cmd = *cmd;
	while (!(*status) && *command != '\0')
	{
		find_next_word(&command, status, &nb_word, &t_cmd->cmd[nb_word]);
		parsing_redir(&command, t_cmd, status, &nb_word);
		if (*command != '\0' && !(*status))
			*status = parsing_ctrl_op(&command, &t_cmd, &nb_word, envp);
		if (*command == '\0' && !t_cmd->cmd[nb_word - 1])
		{
			*status = check_command(&command, status);
			temp = ft_strjoin(save, command);
			free(save);
			save = temp;
		}
	}
	wait_cmd(*cmd, status, HERE_DOC);
	if (*status)
		return (NULL);
	add_history(save);
	free(save);
	return (*cmd);
}

bool	_continue(t_cmd *cmd, char ***envp, int *status, int ctrl)
{
	return (ft_strlen(*cmd->cmd) && !exec_builtins(cmd, status, envp, MAIN)
		&& ((ctrl != AND && ctrl != OR)
			|| ((ctrl == AND && !*status)
				|| (ctrl == OR && *status))));
}

static int	execute(char *command, int *status, char ***envp)
{
	t_cmd	*cmd;
	t_cmd	*r_cmd;
	int		ctrl;

	cmd = NULL;
	ctrl = END;
	*status = 0;
	r_cmd = parsing(command, status, &cmd, *envp);
	while (r_cmd && cmd)
	{
		if (ft_strlen(*cmd->cmd) && exec_pipe(cmd, status, *envp))
			while (cmd->ctrl_op == PIPE)
				cmd = cmd->next;
		else if (_continue(cmd, envp, status, ctrl))
			exec_cmd(cmd, status, *envp, 0);
		ctrl = cmd->ctrl_op;
		cmd = cmd->next;
	}
	if (r_cmd)
		cmd = r_cmd;
	free_cmd(cmd);
	return (*status);
}

void	minishell_loop(int *status, char ***envp)
{
	char	*command;

	while (42)
	{
		printf("status = %d\n", *status);
		signal(SIGINT, handle_prompt);
		signal(SIGQUIT, SIG_IGN);
		command = readline("minishell %");
		if (!command)
			exit(exit_free_envp(envp));
		signal(SIGINT, SIG_IGN);
		printf(">>> %s\n", command);
		if (*command != '\0')
			execute(command, status, envp);
		else
			add_history(command);
		free(command);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		status;

	status = 0;
	if (argc == 1)
	{
		if (init(&envp))
			exit(perror_minishell(errno, "minishell:"));
		minishell_loop(&status, &envp);
	}
	else if (argc > 1 && ft_strncmp(argv[1], "-c", 2) == 0)
		exit(execute(argv[2], &status, &envp));
	dprintf(2, "minshell: %s: invalid option\n"
		"Usage: minishell [option] [command]\n"
		"Shell option :\n\t-c command\n", argv[1]);
	exit(2);
}
