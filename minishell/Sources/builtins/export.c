/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:51:13 by tonted            #+#    #+#             */
/*   Updated: 2022/10/08 19:48:15 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp_alpha(char *prefix, char **env)
{
	char	**env_alpha;

	env_alpha = get_alpha_tabstr(env);
	put_envp(prefix, env_alpha);
	ft_freetabstr(env_alpha);
}

int	exec_export(char *pathname, char **args, char ***envp)
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
		print_envp_alpha("declare -x ", *envp);
	return (1);
}
