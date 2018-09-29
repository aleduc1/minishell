/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 18:17:33 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/29 14:36:08 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **environ)
{
	t_env	env_s;
	t_lst	*env;

	if (ac && av)
	{
		env_cpy(environ, &env);
		read_fct(&env_s, &env);
	}
	return (0);
}
