/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:35:40 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/11 18:36:06 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <libft.h>
# include "../readline/readline.h"
# include "../readline/history.h"
//# include "../sys/ioctl.h"
//# include <readline/readline.h>
//# include <readline/history.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>

extern int	errno;

enum	e_status
{
	NCMD = 1,
	TOKENERR = 258,
	QNC = 259,
};

enum	e_kind
{
	INVISIBLE = 1,
	METACHARACTER = 2,
	R_INVISIBLE = 3,
	R_METACHARACTER = 4,
	INFILE = 5,
	HERE_DOC = 6,
	OUTFILE = 7,
	APPEND = 8,
	BUILTINS = 9,
	CMD = 10,
	MAIN = 11,
	CHILD = 12,
};

enum	e_control_operator
{
	END = 0,//\0
	PIPE = 1, // cree un pipe de sortie
	OR = 2, // continue si ko
	AND = 3, //continue si ok
	BRACE = 4,
};

typedef struct	s_cmd
{
	int				ctrl_op;
	int				status;
	pid_t			pid;
	char			**cmd;
	char			*path;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}				t_cmd;

	//0_env.c

int		init(char ***envp);
	//1_parsing.c

char	*find_next_word(char **command, int *status);
char	check_metacharacter(char **command, int king);
int		parsing_ctrl_op(char **command, t_cmd **cmd, int *nb_word, char **envp);
int 	pass_quote(char **command, int *status);
t_cmd	*ft_mlstadd(t_cmd *cmd, int *status);

	//1-1_parsing_file.c

int		parsing_here_doc(t_cmd *cmd, char *limiter);
int		parsing_redir(char **command, t_cmd *cmd, int *status, int *nb_word);
char	*remove_quote(char *command);

	//1-2_parsing_sub.c
	
int		parsing_and_or(char **command, t_cmd **cmd, int *nb_word);
int		parsing_pipe(char **command, t_cmd **cmd, int *nb_word, char **envp);

	//2_execute.c

void	exec_cmd(t_cmd *cmd, int *status, char **envp, int options);
int		exec_pipe(t_cmd *cmd, int *status, char **envp);

	//3_builtins.c

int		exec_exit(int process, char ***envp);
int		exec_builtins(t_cmd *cmd, int *status, char ***envp, int process);

	//4_utils.c

void	free_cmd(t_cmd *cmd);
void    wait_cmd(t_cmd *cmd, int *status, int ctrl_op);
int		perror_minishell(int status, char *command);
void	handle_prompt(int signum);
void	handle_exec(int sig_num);

 void	print_cmd(t_cmd *cmd);
#endif
