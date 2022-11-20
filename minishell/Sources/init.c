/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 08:58:35 by tonted            #+#    #+#             */
/*   Updated: 2022/11/20 13:43:04 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PATH "PATH"
#define SEP_PATH ":"
#define FOLDER_BIN "/Bin"
#define BIN "minishell"

static void	add_bin_to_path(char ***envp, char *own_path)
{
	char	*tmp1;
	char	*tmp2;
	int		i_path;

	i_path = is_name_in_envp(*envp, PATH);
	if (i_path != -1)
	{
		tmp1 = ft_strjoin(get_value((*envp)[i_path]), SEP_PATH);
		tmp2 = ft_strjoin(tmp1, own_path);
		envp_set_line(envp, tmp2, PATH);
		free_null((void *)tmp1);
		free_null((void *)tmp2);
	}
	else
		envp_set_line(envp, own_path, PATH);
}

static char	*get_own_path(void)
{
	char	*own_path;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	own_path = ft_strjoin(tmp, FOLDER_BIN);
	free_null((void *)tmp);
	return (own_path);
}

int	init(char ***envp)
{
	char	*own_path;
	char	*tmp;

	own_path = get_own_path();
	*envp = ft_dup_cpp(*envp, ft_len_pp((void **)*envp) + 1);
	tmp = find_path(BIN, *envp);
	if (!tmp)
		add_bin_to_path(envp, own_path);
	free_null(own_path);
	free_null(tmp);
	return (EXIT_SUCCESS);
}

static void	init_link(t_cmd *new)
{
	*(new->cmd) = NULL;
	new->ctrl_op = END;
	new->path = NULL;
	new->infile = STDIN_FILENO;
	new->outfile = STDOUT_FILENO;
	new->fd[STDIN_FILENO] = STDIN_FILENO;
	new->fd[STDOUT_FILENO] = STDOUT_FILENO;
	new->flag = 0x0;
	new->next = NULL;
	new->pid = -2;
}

t_cmd	*ft_mlstadd(t_cmd *cmd)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new)
	{
		new->cmd = (char **)ft_calloc(20, sizeof(char *));
		if (new->cmd)
		{
			init_link(new);
			if (cmd)
				cmd->next = new;
			return (new);
		}
		free(new);
	}
	set_status(errno);
	perror("minishell:");
	return (NULL);
}
