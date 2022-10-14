/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 01:25:53 by tonted            #+#    #+#             */
/*   Updated: 2022/10/14 17:34:37 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	*singleton_status(void)
{
	int static	status = 0;

	return (&status);
}

int	get_value_status(void)
{
	return (*singleton_status());
}

void	set_status(int status)
{
	*singleton_status() = status;
}

int	*get_status(void)
{
	return (singleton_status());
}
