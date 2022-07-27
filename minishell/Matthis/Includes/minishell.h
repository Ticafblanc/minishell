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
	NCMD = 1,
	TOKENERR = 258,
	QNC = 259,
};

enum	e_king
{
	INVISIBLE = 1,
	METACHARACTER = 2,
	R_INVISIBLE = 3,
	R_METACHARACTER = 4,
	INFILE = 5,
	HERE_DOC = 6,
	OUTFILE = 7,
	APPEND = 8,
};

enum	e_control_operator
{
	END = 0,//\0
	PIPE = 1, // cree un pipe de sortie
	OR = 2, // continue si ko
	AND = 3, //continue si ok
	BRACE = 4,
	WORD = 5,
};

typedef struct	s_cmd
{
	int				ctrl_op;
	pid_t			pid;
	char			**cmd;
	char			*path;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}				t_cmd;

	//1_parsing.c

char	check_metacharacter(char **command, int king);
int		parsing_ctrl_op(char **command, t_cmd **cmd, int *nb_word);
int 	pass_quote(char **command, int *status);
t_cmd	*ft_mlstadd(t_cmd *cmd, int *status);

	//1-1_parsing_file.c

int		parsing_redir(char **command, t_cmd *cmd, int king);

	//1-2_parsing_here_doc.c
	
int		check_limiter(int fd[2], char *limiter);
// int		parsing_here_doc(char *limiter);

	//1-3_parsing_sub.c
int		parsing_and_or(char **command, t_cmd **cmd, int *nb_word);
int		parsing_pipe(char **command, t_cmd **cmd, int *nb_word);

	//4_utils.c

char 	*remove_quote(char *command);
int		pass_quote(char **command, int *status);
void    free_cmd(t_cmd *cmd);
int		perror_minishell(int status, char *command);

	//2_signal.c
void	handle_prompt(int signum);// gestion de ctrl c dans le prompt
//void	handle_execute(int sig_num);//gestion de ctrl c dans le process


#endif
