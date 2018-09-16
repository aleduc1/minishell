/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 12:20:24 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/12 12:28:18 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dir_functs(char *path, t_env *env_s, t_lst **head)
{
	DIR		*pdir;
	struct dirent	*pent;


	if (env_s && head)
	{
		if (!(pdir = opendir(path)))
		{
			ft_putendl("BRUH TON PATH IL PUE");
			exit(0);
		}
		while ((pent = readdir(pdir)))
		{
			if (pent == NULL)
			{
				ft_putendl("Cant readdir your DIR*");
				exit(0);
			}
			ft_putendl(pent->d_name);
		}
		if (closedir(pdir) == -1)
		{
			ft_putendl("Cant closedir your repository");
			exit(0);
		}
	}
	return (0);
}
