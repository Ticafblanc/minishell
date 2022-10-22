/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_utils.c                                          :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/11 18:30:06 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// char *remove_quote(char *command)
// {
//     int     i;
//     char    c;
//     int     trig;
//     char    *new_command;

//     i =  0;
//     trig = 0;
//     new_command = command;
//     while (*command != '\0')
//     {
//         if (!trig && (*command == 34 || *command == 39))
//         {
//             c = *command;
//             i++;
//             trig = 1;
//         }
//         else if (trig && c == *command)
//         {
//             i++;
//             trig = 0;
//         }
//         *command = *command + i;
//         command++;
//     }
//     return (new_command);
// }


int	perror_minishell(int status, char *command)
{
    if (status == errno)
    {
         dprintf(2,"minishell: %s: %s \n", command, strerror(errno));
         status = 1;
    }
	else if (status == NCMD)
		dprintf(2,"minishell: %s: command not found ", command);
	else if (status == QNC)
		dprintf(2,"minishell: syntax error `%c' not close\n", *command);
	else if (status == TOKENERR)
		dprintf(2,"minishell: syntax error near unexpected token `%s'\n", command);
	return (status);
}
	
void    free_cmd(t_cmd *cmd)
{
    t_cmd   *t_cmd;

    while (cmd)
    {
        t_cmd = cmd;
        free(cmd);
        cmd = t_cmd->next;
    }
}