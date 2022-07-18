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

# define READ_END 	0
# define WRITE_END 	1

enum	e_status
{
	ON = 2,
	MEMO = 3,//cat: stdout: No space left on device
	FORK = 4,
	INFILE = 5,
	OUTFILE = 6,
	PIPE_R = 7,
	TOKEN = 8, //syntax error near unexpected token
	QUOTE = 9,// '' or "" not close
	MAIN = 10,
	SUB = 11,

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
	END = 1,//\0
	PIPE = 2, // cree un pipe de sortie
	OR = 3, // continue si ko
	AND = 4, //continue si ok
	BRACE = 5,// 
	NEWLINE = 6,
};

typedef struct	s_cmd
{
	int				ctrl_op;
	pid_t			pid;
	int				status;//return stat waitpid...
	int				bultin;
	char			*sub;
	char			**cmd;
	char			*path;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}				t_cmd;

	//0_init.c
int	init_minishell(char **envp);// init variable g_global

	//1-2-0_execute.c
char	*execute(char *command);// init la struct de gestion d'une commande 
										//gere les signaux ctrl c et ctrl \
										// recherche une command a executer (une seul)
										// l'envoie dans le parsing pour triage et lance 
										// le dispatch d'execution 

	//1-2-1_parsing.c
// parsing de la strinf cmd->to_do

	//1-2-2_dispatch_execute.c
void	dispatch_execute(t_command *cmd);// open les fichier necessaire selction 
										// et lance l'execution du bon process

	//1-2-2_execute_builtins.c
int		pass_invisible_characters(char *command);

	//1-2-3_execute_builtins.c
//execute bultin passer ne parametre

	//1-2-4_execute_execve.c  
//execute commande passer ne parametre

	//2_signal.c
void	handle_prompt(int signum);// gestion de ctrl c dans le prompt
void	handle_execute(int sig_num);//gestion de ctrl c dans le process

	//3_free_and_exit.c
int		free_and_exit(int exit_code);//gestion de srotie de process et message d'erreur

#endif
