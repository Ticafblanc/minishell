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

# include <libft.h>

	/*define ON/OFF*/
# define	ON		0
# define	OFF		1

	/*define satut*/
# define	ALIVE		0
# define	THINK		1
# define	OWN_FORK	2
# define	RIGHT_FORK	3
# define	EAT			4
# define	SLEEP		5
# define	DEAD		6
# define	DONE		7

# define	ON		0
# define	OFF		1


typedef struct s_global
{
	int				statut;

}				t_global;



	//1_init.c


	//2_start.c

	//3_free_and_exit.c


	


#endif
