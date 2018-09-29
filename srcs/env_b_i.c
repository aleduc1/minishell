/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_b_i.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 16:00:58 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/29 16:03:24 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
