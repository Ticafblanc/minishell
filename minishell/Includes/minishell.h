/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:35:40 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/10/14 02:29:24 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <libft.h>
# include "../readline/readline.h"
# include "../readline/history.h"
# include <sys/ioctl.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>

# define PROMPT "\e[1;36m minishell % \e[0m"
# define WHITESPACES " \t\n\v\f\r"
# define METACHARS "|&()<>"
# define WHITESMETA " \t\n\v\f\r|&()<>"
# define REDIR "<>"
# define OPERATOR "|&"

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

/*
	END		\0
	PIPE 	cree un pipe de sortie
	OR		continue si ko
	AND		continue si ok
	BRACE	
*/
enum	e_control_operator
{
	END = 0,
	PIPE = 1,
	OR = 2,
	AND = 3,
	BRACE = 4,
};

typedef struct s_cmd
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

/* initialization */
int		init(char ***envp);

//1_parsing.c
void	find_next_word(char **command, int *nb_word, char **cmd);
char	check_metacharacter(char **command, int king);
int		manage_operators(char **command, t_cmd **cmd, int *nb_word, char **envp);
int		pass_quote(char **command);
t_cmd	*ft_mlstadd(t_cmd *cmd);

//1-1_parsing_file.c
int		parsing_here_doc(t_cmd *cmd, char *limiter);
int		manage_redir(char **command, t_cmd *cmd, int *nb_word);
char	*remove_quote(char *command);

//1-2_parsing_sub.c	
int		parsing_and_or(char **command, t_cmd **cmd, int *nb_word);
int		parsing_pipe(char **command, t_cmd **cmd, int *nb_word);

/* execute */
void	exec_cmd(t_cmd *cmd, char **envp, int options);
int		exec_pipe(t_cmd *cmd, char **envp);
void	switch_streams(int toclose, int oldfd, int newfd);
void	dup_file(t_cmd *cmd);

/* 3_builtins.c */
int		exec_builtins(t_cmd *cmd, char ***envp, int process);
int		exec_pwd(void);
int		exec_cd(char *dir, char ***envp);
int		exec_unset(t_cmd *cmd, char ***envp);
int		exec_echo(t_cmd *cmd);
void	exec_exit(int process, char ***envp);
int		exec_export(char *pathname, char **args, char ***envp);
int		exec_env(char **envp);

/* utils_env_line */
char	*get_name(char *env_line);
char	*get_value(char *env_line);
int		is_name_in_line(char *envline, char *name);
char	*build_envp_line(char *name, char *value);
void	envp_set_line(char ***envp, char *value, char *name);

/* utils_env */
int		is_name_in_envp(char **envp, char *name);
void	put_envp(char *prefix, char **envp);
char	*find_path(char *cmd, char **envp);

/* utils_free */
void	ft_freetabstr(char **tab);
void	free_cmd(t_cmd *cmd);
void	free_null(void *ptr);

/* utils_libc */
int		ft_strcmp(const char *s1, const char *s2);

/* utils_tabstr */
void	add_line_tabstr(char ***tabstr, char *line);
char	**get_alpha_tabstr(char **tabstr);
char	**tabstrdup(char **tabstr);

/* utils */
int		exit_free_envp(char ***envp);

/* execute */
int		execute(char *command, char ***envp);

/* parsing */
t_cmd	*parsing(char *command, t_cmd **cmd, char **envp);
char	*find_next_word_redir(char **command);

//4_utils.c
void	wait_cmd(t_cmd *cmd, int ctrl_op);
int		perror_minishell(int status, char *command);
void	handle_prompt(int signum);
void	handle_exec(int sig_num);

// Development tools
void	print_cmd(t_cmd *cmd);

/* status */
int		get_status(void);
void	set_status(int status);
int		*get_at_status(void);

#endif
