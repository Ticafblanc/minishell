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

# define READ_END 	0
# define WRITE_END 	1

extern int	errno;

enum	e_status
{
	NCMD = -1,
	TOKENERR = 130,
};

enum	e_bultins
{
	ECHO = 1,
	CD = 2,
	PWD = 3,
	EXPORT = 4,
	UNSET = 5,
	ENV = 6,
	EXIT = 7,
};

enum	e_control_operator
{
	END = 0,//\0
	PIPE = 1, // cree un pipe de sortie
	OR = 2, // continue si ko
	AND = 3, //continue si ok
	BRACE = 4,
	WORD = 5,
	R_IN = 6,
	R_OUT = 7,
	A_R_OUT = 8,
	HERE_DOC = 9,
};

typedef struct	s_cmd
{
	int				ctrl_op;
	pid_t			pid;
	int				bultin;
	char			**cmd;
	char			*path;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}				t_cmd;

	//1_parsing.c

char	check_metacharacter(char c);
int		parsing_invisible_characters(char **command, int *trig);
int		parsing_met(char **command, t_cmd **cmd, int *nb_word, int *trig);
int		add_word(char **command, t_cmd *cmd, int *nb_word, int *trig);
t_cmd	*ft_mlstadd(t_cmd *cmd, int *status);

	//1-1_parsing_file.c

char	find_next_word(char **command, char **file);
int		parsing_app_redir_out(char **command, t_cmd *cmd, int *trig);
int		parsing_redir_out(char **command, t_cmd *cmd, int *trig);
int		parsing_redir_in(char **command, t_cmd *cmd, int *trig);

	//1-2_parsing_here_doc.c
	
int		check_limiter(int fd, char *limiter);
int		parsing_here_doc(char **command, t_cmd *cmd, int *trig);

	//1-3_parsing_sub.c
int		parsing_pipe(char **command, t_cmd **cmd, int *nb_word, int *trig);

int		perror_minishell(int status, char *command);
	//1-2-2_dispatch_execute.c
//void	dispatch_execute(t_command *cmd); open les fichier necessaire selction 
// prepare la list de commande a traiter

	//1-2-2_execute_builtins.c
//int		//pass_invisible_characters(char *command);

	//1-2-3_execute_builtins.c
//execute bultin passer ne parametre

	//1-2-4_execute_execve.c  
//execute commande passer ne parametre

	//2_signal.c
void	handle_prompt(int signum);// gestion de ctrl c dans le prompt
//void	handle_execute(int sig_num);//gestion de ctrl c dans le process

	//3_free_and_exit.c
int		free_and_exit(int status);//gestion de srotie de process et message d'erreur

#endif
