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

# define READ_END 	0
# define WRITE_END 	1

enum	e_statut
{
	ON = 2,
	MEMO = 3,
	FORK = 4,
	INFILE = 5,
	OUTFILE = 6,
	PIPE_R = 7

};

enum	e_flag_end
{
	PIPE = 2, // cree un pipe de sortie
	OR = 3, // continue si ko
	AND = 4, //continue si ok
	APPEND_FILE = 5, //ajoute a un fichier existant le cre au besoin
	REPLACE_FILE = 6, //remplace le contenue du fichier et le remplace au besoin
	END_ERR = 7, //flag non pris en charge
};

typedef struct s_global
{
	int			statut;
	char		**envp;
	char		*command;
}				t_global;

typedef struct s_command
{
	int			flag_start;// flag de but de command
	int			flag_end; //flag de fin de command
	char		*to_do; //command a traiter	
	char		**cmd;
	char		*path;
	int			infile;
	int			outfile;
}			t_command;

	//0-0_init.c
void	init_minishell(void);

	//0-1_start.c
void	start_minishell(void);
void	execute_command(char *command);

	//0-1-0_signal.c
void	handle_prompt(int signum);

	//0-1-1_prompt.c
int		prompt_minishell(void);
int		check_add_history(char *command);

void	dispatch_execute(t_command *cmd);
int		pass_invisible_characters(char *command);
	//0-2_free_and_exit.c
int		free_and_exit(int exit_code);

#endif
