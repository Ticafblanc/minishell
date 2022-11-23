/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:35:40 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/11/23 13:18:27 by tblanco          ###   ########.fr       */
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
# include "colors.h"

# define PROMPT "\e[1;36m minishell % \e[0m"
# define WHITESPACES " \t\n\v\f\r"
# define METACHARS "|&()<>"
# define WHITESMETA " \t\n\v\f\r|&()<>"
# define REDIR "<>"
# define OPERATOR "|&"
# define BRACES "()"
# define F_HD 0x1
# define F_FIRST 0x2

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
	pid_t			pid;
	int				fd[2];
	char			**cmd;
	char			flag;
	char			*path;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
	char			*command;
}				t_cmd;

/* initialization */
int		init(char ***envp);

/* status */
int		get_value_status(void);
void	set_status(int status);
int		*get_status(void);
int		*last_status(void);

/* handle_signals */
void	handle_prompt(int signum);
void	handle_exec(int sig_num);
void	handle_exe(int sig_num);

/* parsing */
t_cmd	*parsing(char *command, t_cmd **cmd, char **envp);
t_cmd	*ft_mlstadd(t_cmd *cmd);
int		manage_redir(char **command, t_cmd *cmd, int *nb_word);
int		manage_ope(char **command, t_cmd **cmd, int *nb_word, char **envp);
int		manage_braces(char **command, t_cmd **cmd, int *nb_word, char **envp);
void	manage_args(t_cmd *cmd, char **envp);
void	manage_wildcard(t_cmd *cmd);
bool	search_files(t_cmd *cmd, int i_cmd);
void	parsing_loop(char *command, t_cmd *t_cmd, char **envp, char **save);

/* utils parsing */
bool	strmatch(char *str, char *pattern);
void	find_next_word(char **command, int *nb_word, char **cmd);
char	*find_next_word_redir(char **command);
char	check_metacharacter(char **command, int king);
char	*remove_quote(char *command);

/* execute */
int		execute(char *command, char ***envp);
int		exec_pipe(t_cmd *cmd, char **envp);
void	exec_cmd(t_cmd *cmd, char **envp, int options);
void	interpret_vars(t_cmd *cmd, int i, int i_cmd, char **envp);

/* utils execute */
void	switch_streams(int toclose, int oldfd, int newfd);
void	dup_file(t_cmd *cmd);
void	wait_cmd(t_cmd *cmd, int ctrl_op);
void	close_pipe_fd(t_cmd *cmd);

/* builtins.c */
int		exec_builtins(t_cmd *cmd, char ***envp, int process);
int		exec_pwd(int fd);
int		exec_cd(char *dir, char ***envp);
int		exec_unset(t_cmd *cmd, char ***envp);
int		exec_echo(t_cmd *cmd, int fd);
int		exec_exit(int process, char ***envp, char **cmd);
int		exec_export(char *pathname, char **args, char ***envp, int fd);
int		exec_env(char **envp, int fd);

/* utils_env */
void	wait_pipe(t_cmd *cmd);
void	envp_set_line(char ***envp, char *value, char *name);
char	*get_name(char *env_line);
char	*get_value(char *env_line);
int		is_name_in_line(char *envline, char *name);
int		is_name_in_envp(char **envp, char *name);
void	put_envp(char *prefix, char **envp, int fd);
char	*find_path(char *cmd, char **envp);
char	*find_path_child(char *cmd, char **envp);

/* utils error */
int		perror_minishell(int status, char *command);

/* utils_free */
void	ft_freetabstr(char **tab);
void	free_null(void *ptr);
int		exit_free_envp(char ***envp);
void	free_next_cmds(t_cmd *cmd);
void	wait_next_cmds(t_cmd *cmd);

/* utils_libc */
int		ft_strcmp(const char *s1, const char *s2);

/* utils_tabstr */
void	add_line_tabstr(char ***tabstr, char *line);
char	**get_alpha_tabstr(char **tabstr);
char	**tabstrdup(char **tabstr);

/* Development tools */
void	print_cmd(t_cmd *cmd);
void	print_cmds(t_cmd *cmd);

#endif
