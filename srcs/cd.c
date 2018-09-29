/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 15:55:59 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/29 15:59:14 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_lst(t_lst **head)
{
	t_lst	*curlist;
	t_lst	*prevlist;

	curlist = *head;
	while (curlist)
	{
		ft_strdel(&(curlist->key));
		ft_strdel(&(curlist->value));
		prevlist = curlist->next;
		free(curlist);
		curlist = prevlist;
	}
}

int		ft_getarg(char *str)
{
	int		args;

	args = 0;
	args = ft_atoi(str);
	return (args);
}

void	ft_cd_pt_1(t_env *env_s, t_lst **head)
{
	char	cwd[4096];

	if ((env_s->tab[1]) && (env_s->tab[1][0] != '-'))
	{
		if (!(access(env_s->tab[1], X_OK) == 0))
			ft_putendl("File doesnt exist");
		else
		{
			if (chdir(env_s->tab[1]) == -1)
				ft_putendl("The argument isnt an accessible repository");
			else
			{
				getcwd(cwd, 4096);
				setoldpwd(head);
				modify_value("PWD", cwd, head);
			}
		}
	}
	else
		ft_cd_pt_2(env_s, head);
}

void	ft_cd_pt_2(t_env *env_s, t_lst **head)
{
	char	*value;
	char	cwd[4096];

	if (env_s->tab[1])
	{
		value = get_value_of_key(head, "OLDPWD");
		if (!(access(value, X_OK) == 0))
			ft_putendl("File doesnt exist");
		else
		{
			if (chdir(value) == -1)
				ft_putendl("The argument isnt an accessible repository");
			else
			{
				getcwd(cwd, 4096);
				setoldpwd(head);
				modify_value("PWD", cwd, head);
			}
		}
		free(value);
	}
	else
		ft_cd_pt_3(head);
}

void	ft_cd_pt_3(t_lst **head)
{
	char	*home;

	if (!(home = get_value_of_key(head, "HOME")))
	{
		ft_putendl("Error : A var in your ENV is needed");
		return ;
	}
	chdir(home);
	setoldpwd(head);
	modify_value("PWD", home, head);
	free(home);
}
