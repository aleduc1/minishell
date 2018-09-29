/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 00:59:45 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/29 16:04:38 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo_pt_1(t_env *env_s, t_lst **head)
{
	if (head)
	{
		if (env_s->tab[1])
			ft_echo_pt_2(env_s);
		else
			ft_putendl("");
	}
}

void	ft_echo_pt_2(t_env *env_s)
{
	int		i;

	i = 1;
	while (env_s->tab[i])
	{
		if (!(ft_strcmp(env_s->tab[1], "-n")))
		{
			if (env_s->tab[i + 1])
			{
				if (i > 1 && env_s->tab[i - 2])
					ft_putchar(' ');
				ft_putstr(env_s->tab[i + 1]);
			}
		}
		else
		{
			if (i - 1 > 0 && env_s->tab[i - 1])
				ft_putchar(' ');
			ft_putstr(env_s->tab[i]);
		}
		i++;
	}
	if ((ft_strcmp(env_s->tab[1], "-n")))
		ft_putchar('\n');
}

void	ft_exit(t_env *env_s, t_lst **head)
{
	int		arg;

	if (head)
	{
		if (env_s->tab[1])
		{
			if (env_s->tab[1][0])
			{
				arg = ft_getarg(env_s->tab[1]);
				free_struct(env_s);
				del_lst(head);
				exit(arg);
			}
		}
		else
		{
			free_struct(env_s);
			del_lst(head);
			exit(0);
		}
	}
}

void	ft_setenv(t_env *env_s, t_lst **head)
{
	char	**tab;
	int		i;

	i = 1;
	while (env_s->tab[i])
	{
		if ((tab = split_once(env_s->tab[i], '=')))
		{
			if (tab[1])
			{
				if (lst_check_name(tab[0], head))
					modify_value(tab[0], tab[1], head);
				else
					put_in_list(tab, head);
			}
			else
				ft_putendl("Error : Usage = setenv key=value");
		}
		else
			ft_putendl("Error : Usage = setenv key=value");
		if (tab)
			free_double_tab(tab);
		i++;
	}
}

void	ft_unsetenv(t_env *env_s, t_lst **head)
{
	int		i;

	i = 1;
	while (env_s->tab[i])
	{
		if (env_s->tab[i])
		{
			if (lst_check_name(env_s->tab[i], head))
				del_a_node(env_s->tab[i], head);
		}
		else
			ft_putendl("Error : Usage = unsetenv key");
		i++;
	}
}
