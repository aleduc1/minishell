/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:20:24 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/17 20:30:36 by aleduc           ###   ########.fr       */
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
	exit (-1);
}

int		dir_functs(char *filename, t_env *env_s)
{
	DIR				*pdir;
	struct dirent	*pent;
	int				error;

	error = 1;
	if (!(pdir = opendir(filename)))
		ft_error(error);
	while ((pent = readdir(pdir)))
	{
		if (pent == NULL)
			ft_error((error = 2));
		if (!(ft_strcmp(pent->d_name, env_s->tab[0])))
		{
			if (closedir(pdir) == -1)
				ft_error((error = 3));
			return (1);
		}
	}
	if (closedir(pdir) == -1)
		ft_error((error = 3));
	return (0);
}

void	ft_fork_exec(char *filename, t_env *env_s, t_lst **head)
{
	char	*path;

	path = NULL;
	ft_putstr("Salut j'ai trouver l'executable dans le dossier : ");
	ft_putendl(filename);
	if (filename && env_s && head)
	{
		path = create_path(filename, env_s->tab[0]);
		if (!(access(path, X_OK) == 0))
			return ;
		else
		{
			return ;
		}
		return ;
	}
	return ;
}
