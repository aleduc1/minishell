/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 18:17:33 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/25 22:33:56 by aleduc           ###   ########.fr       */
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

/*
 * main(ac, av, env);*
 * env_cpy*
 * get_next_line(STDIN_FILENO, &line) en boucle infini*
 * afficher le prompt*
 * si get_next_line a return qque chose alors l'interpreter	*
 * pour interpreter &line -> Parser	*
 * Recuperer commande et built-in*
 * Recuperer options*
 * Recuperer arguments*
 * Check si commande = built-in, si oui l'executer *
 * L'envoyer chercher le binaire dans le $PATH sinon
 * Coder les 6 builts-in pour le faire meme sans $PATH
 * */
