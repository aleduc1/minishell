/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/17 17:45:37 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/23 18:13:29 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_tab(char **tab)
{
	int	count;

	count = 0;
	while (tab[count])
	{
		ft_strdel(&(tab[count]));
		count++;
	}
	free(tab);
	tab = 0;
}

void	free_struct(t_env *env_s)
{
	if (env_s->line)
		free(env_s->line);
	if (env_s->tab)
		free_double_tab(env_s->tab);
}
