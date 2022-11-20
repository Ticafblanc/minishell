/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:51:13 by tonted            #+#    #+#             */
/*   Updated: 2022/11/20 13:02:49 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_envp_alpha(char *prefix, char **env, int fd)
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
	if (!(ft_len_pp((void **)args) > 1))
	{
		print_envp_alpha("declare -x ", *envp, fd);
		return (1);
	}
	while (args[++i])
	{
		if (!ft_isalnum(args[i][0]))
		{
			dprintf(2, "minishell: export: `%c': not a valid identifier\n",
				args[i][0]);
			set_status(TOKENERR);
		}
		else
			envp_set_line(envp, get_value(args[i]), get_name(args[i]));
	}
	return (1);
}
