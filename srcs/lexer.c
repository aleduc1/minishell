/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 15:04:59 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/29 14:34:27 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_lexer(t_env *env_s)
{
	env_s->tab = ft_split_whitespaces(env_s->line);
	env_s->bin = 0b000000;
	if (env_s->tab[0])
	{
		env_s->bin = env_s->bin
			| B_CD * (!(ft_strcmp(env_s->tab[0], "cd")))
			| B_ECHO * (!(ft_strcmp(env_s->tab[0], "echo")))
			| B_EXIT * (!(ft_strcmp(env_s->tab[0], "exit")))
			| B_ENV * (!(ft_strcmp(env_s->tab[0], "env")))
			| B_SETENV * (!(ft_strcmp(env_s->tab[0], "setenv")))
			| B_UNSETENV * (!(ft_strcmp(env_s->tab[0], "unsetenv")));
		return (0);
	}
	return (1);
}

void	set_tab_fptr(t_env *env_s)
{
	env_s->ptrf = (t_fptr *)ft_memalloc(sizeof(t_fptr) * 7);
	env_s->ptrf[0].f = &ft_cd_pt_1;
	env_s->ptrf[0].bitmask = B_CD;
	env_s->ptrf[1].f = &ft_echo_pt_1;
	env_s->ptrf[1].bitmask = B_ECHO;
	env_s->ptrf[2].f = &ft_exit;
	env_s->ptrf[2].bitmask = B_EXIT;
	env_s->ptrf[3].f = &ft_env;
	env_s->ptrf[3].bitmask = B_ENV;
	env_s->ptrf[4].f = &ft_setenv;
	env_s->ptrf[4].bitmask = B_SETENV;
	env_s->ptrf[5].f = &ft_unsetenv;
	env_s->ptrf[5].bitmask = B_UNSETENV;
	env_s->ptrf[6].f = NULL;
	env_s->ptrf[6].bitmask = 0;
}

void	ft_parser(t_env *env_s, t_lst **head)
{
	env_s->count = 0;
	set_tab_fptr(env_s);
	while (env_s->ptrf[env_s->count].f)
	{
		if (env_s->bin == env_s->ptrf[env_s->count].bitmask)
			env_s->ptrf[env_s->count].f(env_s, head);
		env_s->count++;
	}
	free(env_s->ptrf);
}
