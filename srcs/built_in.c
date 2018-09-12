/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 00:59:45 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/12 18:27:20 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_getarg(char *str)
{
	int		args;

	args = 0;
	args = ft_atoi(str);
	return (args);
}

void	ft_cd_pt_1(t_env *env_s, t_lst **head)
{
	char	*cwd;

	cwd = NULL;
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
				setpwd(cwd, head);
			}
		}
	}
	else
		ft_cd_pt_2(env_s, head);
}

void	ft_cd_pt_2(t_env *env_s, t_lst **head)
{
	char	*value;
	char	*cwd;

	cwd = NULL;
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
				setpwd(cwd, head);
			}
		}
	}
	else
		ft_cd_pt_3(head);
}

void	ft_cd_pt_3(t_lst **head)
{
	char	*home;

	home = get_value_of_key(head, "HOME");
	chdir(home);
	setoldpwd(head);
	setpwd(home, head);
}

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
				free(env_s->ptrf);
				free(env_s->tab);
				exit(arg);
			}
		}
		else
			exit(0);
	}
}

/* Simplified version, just print env for now */

void	ft_env(t_env *env_s, t_lst **head)
{
	if (env_s)
		ft_print_env(head);
}

/* If key exist replace his value, else add a whole new node in the env list */

void	ft_setenv(t_env *env_s, t_lst **head)
{
	char	**tab;
	int		i;

	i = 1;
	while (env_s->tab[i])
	{
		if (env_s->tab[i])
		{
			tab = ft_strsplit(env_s->tab[i], '=');
			if (tab[1])
			{
				if (lst_check_name(tab[0], head))
					modify_value(tab[0], tab[1], head);
				else
					put_in_list(tab, head);
			}
			else
				ft_putendl("Error : Usage = setenv key=value");
			free_double_tab(tab);
		}
		else
			ft_putendl("Error : Usage = setenv key=value");
		i++;
	}
}

/* if key exist, add fonction to del a node */

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
