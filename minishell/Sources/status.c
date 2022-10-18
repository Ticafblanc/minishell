/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 01:25:53 by tonted            #+#    #+#             */
/*   Updated: 2022/10/17 18:18:41 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	*singleton_status(void)
{
	int static	status = 0;

	return (&status);
}

int	*last_status(void)
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
