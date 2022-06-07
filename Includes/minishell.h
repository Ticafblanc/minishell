/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguay <aguay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:26 by aguay             #+#    #+#             */
/*   Updated: 2022/06/07 13:13:05 by aguay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef MINISHELL_H
# define MINISHELL_H

# include "commands.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_flags
{
	bool	exit;
}			t_flags;

//	main engine
char	*routine_prompt(void);

//	Parsing functions
void	parsing(t_flags *flags, char *entry);

#endif