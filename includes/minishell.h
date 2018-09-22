/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleduc <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 18:01:18 by aleduc            #+#    #+#             */
/*   Updated: 2018/09/22 19:24:29 by aleduc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <dirent.h>
# include <sys/types.h>

# define B_CD		0b000001
# define B_ECHO		0b000010
# define B_EXIT		0b000100
# define B_ENV		0b001000
# define B_SETENV	0b010000
# define B_UNSETENV	0b100000

typedef struct s_env t_env;
typedef struct s_fptr t_fptr;


struct s_env
{
	char	**key_value;
	char	*line;
	char	**tab;
	int		bin;
	t_fptr	*ptrf;
	int		count;
};

struct s_fptr
{
	void	(*f)(t_env *, t_lst **head);
	int		bitmask;
};

/* Create own env */

void	env_cpy(char **environ, t_lst **env);
char	**ft_first_cut(char **env);
void	ft_scd_cut(char **one_cut, t_env *env_s);
void	put_in_list(char **scd_cut, t_lst **head);

/* Expanses */

char	*replace(t_env *env_s, char *key, char *name, t_lst **head);
int		expanse(t_env *env_s, t_lst **head);
int		delimiter(char c);
char	*to_check(char *str);

/* List manipulation */

t_lst	*create_node(char **scd_cut);
void	add_node(t_lst **head, t_lst *node);
void	ft_print_env(t_lst **head);
void	del_a_node(char *key, t_lst **head);
void	check_first_node(char *key, t_lst **head);
int		lst_check_name(char *name, t_lst **head);
void	modify_value(char *key, char *value, t_lst **head);
char	*get_value_of_key(t_lst **head, char *key);
void	setoldpwd(t_lst **head);
void	setpwd(char *cwd, t_lst **head);
char	**list_to_char(t_lst **head);
void	del_lst(t_lst **head);

/* Reading input */

void	ft_search_bin(t_env *env_s, t_lst **head);
void	read_fct(t_env *env_s, t_lst **head);

/* Dir functions */

void	ft_error(int code);
int		dir_functs(char *filename, t_env *env_s);
int		ft_fork_exec(char *filename, t_env *env_s, t_lst **head);
char	*create_path(char *filename, char *bin);
void	call_bin(char *binpath, t_env *env_s, t_lst **head);

/* Lexing-Parsing */

int		ft_lexer(t_env *env_s);
void	ft_parser(t_env *env_s, t_lst **head);
void	set_tab_fptr(t_env *env_s);

/* Built_in */

int		ft_getarg(char *str);

void	ft_cd_pt_1(t_env *env_s, t_lst **head);
void	ft_cd_pt_2(t_env *env_s, t_lst **head);
void	ft_cd_pt_3(t_lst **head);

void	ft_echo_pt_1(t_env *env_s, t_lst **head);
void	ft_echo_pt_2(t_env *env_s);

void	ft_exit(t_env *env_s, t_lst **head);

void	ft_env(t_env *env_s, t_lst **head);

void	ft_setenv(t_env *env_s, t_lst **head);

void	ft_unsetenv(t_env *env_s, t_lst **head);

/* Free fonctions */

void	free_double_tab(char **tab);
void	free_struct(t_env *env_s);
#endif
