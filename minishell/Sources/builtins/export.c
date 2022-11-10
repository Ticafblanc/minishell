/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:51:13 by tonted            #+#    #+#             */
/*   Updated: 2022/11/10 11:08:31 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void static	print_envp_alpha(char *prefix, char **env, int fd)
{
	char	**env_alpha;

	env_alpha = get_alpha_tabstr(env);
	put_envp(prefix, env_alpha, fd);
	ft_freetabstr(env_alpha);
}

int	exec_export(char *pathname, char **args, char ***envp, int fd)
{
	int		i;

	(void) pathname;
	(void) args;
	(void) envp;
	i = 0;
	if (ft_len_pp((void **)args) > 1)
		while (args[++i])
			envp_set_line(envp, get_value(args[i]), get_name(args[i]));
	else
		print_envp_alpha("declare -x ", *envp, fd);
	return (1);
}
