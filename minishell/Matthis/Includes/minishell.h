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
# include "../sys/ioctl.h"
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
};

enum	e_command
{
	PIPE = 2, // cree un pipe de sortie
	OR = 3, // continue si ko
	AND = 4, //continue si ok
	S_BRACE = 5,// debut de parentese
	I_BRACE = 6,//mileu ...
	E_BRACE = 7,//fin ...

};

typedef struct s_global
{
	int				statut;
	char			**envp;
	char			*command;
	int				*flag_command[4];// [0] input [1] output [2] option [3] braces


}				t_global;

typedef struct s_command
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
}			t_command;

	//1_init.c
void	init_minishell(void);

	//2_start.c
void	start_minishell(void);

	//3_signal.c
void	monitor_sigint(int signum);

	//4_prompt.c
void	prompt_minishell(void);

	//_free_and_exit.c
int		free_and_exit(int exit_code);

#endif
