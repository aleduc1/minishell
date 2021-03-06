/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 17:06:41 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/29 14:43:25 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		isdir(const char *file)
{
	struct stat	buff;

	if (lstat(file, &buff) == -1)
		return (0);
	else
	{
		if ((buff.st_mode & 0170000) == 0040000)
			return (1);
	}
	return (0);
}

void	error_msg(int code, t_env *env_s)
{
	if (code == 0)
	{
		ft_putstr("minishell: command not found");
		if (env_s->tab[0])
		{
			ft_putstr(": ");
			ft_putendl(env_s->tab[0]);
		}
	}
}

void	bin_by_path(int *code, t_env *env_s, t_lst **head)
{
	if (*code == 0 && (access(env_s->tab[0], X_OK) == 0) \
			&& (isdir(env_s->tab[0]) == 0))
	{
		call_bin(env_s->tab[0], env_s, head);
		*code = 1;
	}
}

void	ft_search_bin(t_env *env_s, t_lst **head)
{
	char	*envpath;
	char	**paths;
	int		counts;
	int		code;

	paths = NULL;
	code = 0;
	counts = 0;
	if (lst_check_name("PATH", head))
	{
		envpath = get_value_of_key(head, "PATH");
		paths = ft_strsplit(envpath, ':');
		free(envpath);
		while (paths[counts])
		{
			if (dir_functs(paths[counts], env_s) == 1)
				break ;
			counts++;
		}
		if (paths[counts])
			code = ft_fork_exec(paths[counts], env_s, head);
		free_double_tab(paths);
	}
	bin_by_path(&code, env_s, head);
	error_msg(code, env_s);
}

void	read_fct(t_env *env_s, t_lst **head)
{
	while (42)
	{
		ft_putstr("~> ");
		if (get_next_line(STDIN_FILENO, &env_s->line))
		{
			if (env_s->line[0])
			{
				while (dollars(env_s, head))
					;
				tilde(env_s, head);
				ft_lexer(env_s) == 0 ? ft_parser(env_s, head) : 0;
				if (env_s->bin == 0)
				{
					if ((env_s->tab[0]) && ft_strcmp(env_s->tab[0], "/"))
						ft_search_bin(env_s, head);
				}
				if (env_s->tab)
					free_double_tab(env_s->tab);
			}
		}
		if (env_s->line)
			free(env_s->line);
	}
}
