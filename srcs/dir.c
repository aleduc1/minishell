/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:20:24 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/17 23:04:00 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(int code)
{
	if (code == 1)
		ft_putendl("opendir failed");
	else if (code == 2)
		ft_putendl("readdir failed");
	else if (code == 3)
		ft_putendl("closedir failed");
	else if (code == 4)
		ft_putendl("Path creation failed");
}

int		dir_functs(char *filename, t_env *env_s)
{
	DIR				*pdir;
	struct dirent	*pent;

	if (!(pdir = opendir(filename)))
		ft_error(1);
	while ((pent = readdir(pdir)))
	{
		if (pent == NULL)
			ft_error(2);
		if (!(ft_strcmp(pent->d_name, env_s->tab[0])))
		{
			if (closedir(pdir) == -1)
				ft_error(3);
			return (1);
		}
	}
	if (closedir(pdir) == -1)
		ft_error(3);
	return (0);
}

char	*create_path(char *filename, char *bin)
{
	char	*path;
	char	*tmp;

	path = ft_strjoin(filename, "/");
	tmp = path;
	path = ft_strjoin(path, bin);
	free(tmp);
	return (path);
}

int		ft_fork_exec(char *filename, t_env *env_s, t_lst **head)
{
	char	*path;

	path = NULL;
	if (filename && env_s && head)
	{
		if (!(path = create_path(filename, env_s->tab[0])))
			ft_error(4);
		if (!(access(path, X_OK) == 0))
			return ;
		else
		{
			ft_putendl("a");
//			call_bin(path, head);
			return ;
		}
		return ;
	}
	return ;
}
