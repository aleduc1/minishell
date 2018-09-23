/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 00:59:45 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/23 16:59:10 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_lst(t_lst **head)
{
	t_lst	*curlist;

	curlist = *head;
	while (curlist)
	{
		ft_strdel(&(curlist->key));
		ft_strdel(&(curlist->value));
		*head = curlist->next;
		curlist->next = NULL;
		free(curlist);
		curlist = *head;
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

	home = get_value_of_key(head, "HOME");
	chdir(home);
	setoldpwd(head);
	modify_value("PWD", home, head);
	free(home);
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
	while (env_s->tab[i]) // tant que y a des arguments
	{
		if ((tab = split_once(env_s->tab[i], '=')))// split l'arg sur = une fois
		{
			if (tab[1]) // si y a bien key et value
			{
				if (lst_check_name(tab[0], head))
					modify_value(tab[0], tab[1], head);
				else
					put_in_list(tab, head);
			}
			else
				ft_putendl("Error : Usage = setenv key=value");
		}
		else // si ya juste key ou pas de = -> mettre l'usage
			ft_putendl("Error : Usage = setenv key=value");
		if (tab)
			free_double_tab(tab);
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
