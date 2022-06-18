/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-1-2-4_execute_utils.c                            :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/11 18:30:06 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	pass_invisible_characters(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (check_invisible_characters(command[i]) == 0)
			return (i);
		i++;
	}
	return (0);
}

// void	check_output_character(char *command)
// {
// 	int	i;

// 	i = 0;
// 	while (command[i] && command[i] != '|'
//             || (command[i] != '&' && command [i + 1] != '&')
//             || command[i] != '(' || command[i] != '>')
//             i++;
// 	return (i);
// }

// void	add_file_name(char *command)
// {
// 	int 	i;
	
// 	i = 0;
// 	while (check_invisible_characters(command[i]))
// 			i++;
// 	while (!check_invisible_characters(command[i]))
// 			i++;
// 	return (i);
// }
