/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 00:59:45 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/29 14:55:20 by aleduc           ###   ########.fr       */
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

void	ft_env(t_env *env_s, t_lst **head)
{
	t_lst	*newlist;
	t_env	newenv;
	int		setenv_ret;

	setenv_ret = 0;
	newlist = NULL;
	if (!(env_s->tab[1]))
		ft_print_env(head);
	else
	{
		cpy_lst(&newlist, head);
		if ((setenv_ret = manage_setenv(&newlist, env_s)) == 0)
			ft_print_env(&newlist);
		else
		{
			create_newenv(&newenv, env_s, setenv_ret);
			exec_env(&newenv, &newlist);
		}
		del_lst(&newlist);
	}
}

void	create_newenv(t_env *dst, t_env *src, int here)
{
	int		size;
	int		i;
	int		start;

	size = 0;
	i = 0;
	start = here;
	while (src->tab[here])
	{
		size = size + ft_strlen(src->tab[here]) + 1;
		here++;
	}
	if (!(dst->line = (char *)ft_memalloc(sizeof(char) * (size + 1))))
		return ;
	while (src->tab[start])
	{
		ft_strcat(dst->line, src->tab[start]);
		i = ft_strlen(dst->line);
		dst->line[i] = ' ';
		start++;
	}
}

void	exec_env(t_env *newenv, t_lst **newlist)
{
	ft_lexer(newenv) == 0 ? ft_parser(newenv, newlist) : 0;
	if (newenv->bin == 0)
	{
		if ((newenv->tab[0]) && ft_strcmp(newenv->tab[0], "/"))
			ft_search_bin(newenv, newlist);
	}
	if (newenv->tab)
		free_double_tab(newenv->tab);
	if (newenv->line)
		free(newenv->line);
}

void	man_set_2(char **tab, t_lst **newlist, int *return_value, int *i)
{
	if (tab[1])
	{
		if (lst_check_name(tab[0], newlist))
			modify_value(tab[0], tab[1], newlist);
		else
			put_in_list(tab, newlist);
	}
	else
		*return_value = *i;
}

int		manage_setenv(t_lst **newlist, t_env *env_s)
{
	char	**tab;
	int		i;
	int		return_value;

	return_value = 0;
	i = 1;
	while (env_s->tab[i] && return_value == 0)
	{
		if ((tab = split_once(env_s->tab[i], '=')))
			man_set_2(tab, newlist, &return_value, &i);
		else
			return_value = i;
		if (tab)
			free_double_tab(tab);
		i++;
	}
	return (return_value);
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
