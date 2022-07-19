/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-2-1_parsing.c                                    :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern char	**g_envp;

int     parsing_pipe(char **command, t_cmd *cmd, int *nb_word, int *trig)
{
    perror("bash: syntax error near unexpected token `|'");
    if (ft_strncmp(command + *i, "||", 2))
    {
		cmd->ctrl_op = OR;
        parsing_last(ft_strtok(NULL, '|'), cmd);
        *i += ft_str_len(cmd) + 2;
    }

     else
    {
        cmd->ctrl_op = PIPE;
        cmd->cmd = (char **)ft_calloc(4, sizeof(char *));
	    if (!cmd->cmd)
        {
            //gestion de errue a imprimmer;
            return (-1);
        }
        cmd->cmd[0] = ft_substr("/minishell", 0, 10);  
        cmd->cmd[1] = ft_substr("-c", 0, 2);// gestion erreur de retour sub a faire 
        cmd->cmd[2] = ft_strtok(NULL, '|');
         *i += ft_str_len(cmd->cmd[2]) + 1;
    }
    return(0);
}

int     parsing_and(char *command, int *i, t_cmd *cmd, int *nb_word, int *trig)
{
    if (ft_strncmp(command + *i, "&&", 2))
    {
		cmd->ctrl_op = AND;
        parsing_last(ft_strtok(NULL, '&'), cmd);
        *i += 2;
    }
    else
    {
        //gestion de errue a imprimmer;erreur token &
        return (-1);
    }
    return (0);
}

// int     parsing_brace(char *command, int *i, t_cmd *cmd)
// {
//     char    *tmp;

//     if (command[*i] == '(')
//     {
//         tmp = ft_strtok(NULL, '(');
//         while (*tmp)
//         {
//             if (check_invisible_characters(*tmp))
//                 tmp++;
//             else
//             {
//                 printes strtok du mot en errreu;
//                 return (-1);
//             }
//         }
//         cmd->ctrl_op = BRACE;
//         cmd->cmd = (char **)ft_calloc(4, sizeof(char *));
// 	    if (!cmd->cmd)
//         {
//             //gestion de errue a imprimmer;
//             return (-1);
//         }
//         cmd->cmd[0] = ft_substr("/minishell", 0, 10);
//         cmd->cmd[1] = ft_substr("-c", 0, 2);// gestion erreur de retour sub a faire 
//         cmd->cmd[2] = ft_strtok(NULL, '|');
//          *i += ft_str_len(cmd->cmd[2]) + 2;
                


//     }
//     else
//     {
//         //gestion de erreur pour ) a imprimmer;
//         return (-1);
//     }
// }
int	 here_doc(int fd, char *limiter)
{
	char	*line;

	close(fd[FD_READ]);
	if (check_limiter(fd[FD_WRITE], limiter) == 1)
		exit(EXIT_SUCCESS);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			close(fd);
			free(line);
			return (0);
		}
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd);
	free(line);
	return (-1);
}

int     parsing_infile(char *command, int *i, t_cmd *cmd)
{
    pid_t	pid;
	int		fd[2];
    char    *save;
    char    *tok;

    save = ft_strtok(NULL, '<');
	if (ft_strncmp(command + *i, "<<", 2) == 0)
	{
        ft_strtok(NULL, '<');//finfgd next token
        if (pipe(fd) == -1)
		    return (free_and_errro(PIPE));
        cmd->infile = fd[READ_END];
	    pid = fork();
	    if (pid == -1)
		    return (free_and_error(FORK));
	    if (pid == 0)
	    {
		    here_doc(fd[FD_WRITE], argc);
	    }
    }
	else
	{
		cmd->infile = open(argv[1], O_RDONLY, 0777);
	}
	if (cmd->infile == -1)
    {
        free_and_error(INFILE);
        return (-1);
    }
	return (0);
}

int     parsing_outfile(char *command, int *i, t_cmd *cmd)
{
    char    *tok;

    tok = ft_strtok(NULL, '>')
    if (ft_strncmp(command + *i, ">>", 2) == 0)
    {
        cmd->outfile = open(tok,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
        *i += ft_str_len(tok) + 2;
    }
    else
    {
        cmd->outfile = open(tok,
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
        *i += ft_str_len(tok) + 1;
    }
    if (cmd->outfile == -1)
    {
        free_and_error(OUTFILE);
        return (-1);
    }
    return (0);
}


	