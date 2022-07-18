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

int     parsing_pipe(char *command, int *i, t_cmd *cmd)
{
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

int     parsing_and(char *command, int *i, t_cmd *cmd)
{
    if (ft_strncmp(command + *i, "&&", 2))
    {
		cmd->ctrl_op = AND;
        parsing_last(ft_strtok(NULL, '&'), cmd);
        *i += 2;
    }
    else if (command[i] == '\n')///voir comportement avant la fin duparsing
    {
        cmd->ctrl_op = NEWLINE;
        parsing_last(ft_strtok(NULL, '\n'), cmd)
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

	