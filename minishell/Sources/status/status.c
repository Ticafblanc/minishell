/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 01:25:53 by tonted            #+#    #+#             */
/*   Updated: 2022/10/14 02:29:31 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	*singleton_status(void)
{
	int static	status = 0;

	return (&status);
}

int	get_status(void)
{
	int	*tmp;
	tmp = singleton_status();
	return (*tmp);
}

void	set_status(int status)
{
	int	*tmp;
	tmp = singleton_status();
	*tmp = status;
}

int	*get_at_status(void)
{
	return (singleton_status());
}
