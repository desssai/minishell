/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:18:03 by ncarob            #+#    #+#             */
/*   Updated: 2022/03/10 18:42:58 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

# define MAX_PATH 1024

# define MLC_ERROR "minishell: memory allocation error\n"
# define CMD_ERROR "minishell: parsing error\n"

typedef struct s_shell
{
	int				exit_status;
	int				shell_level;
}				t_shell;

// Environment variables list structure.

typedef struct s_envars
{
	char				*key;
	char				*value;
	struct s_envars		*next;
}	t_envars;

// Commands list structure.

typedef struct s_comnds
{
	char			*command;
	char			*outfile;
	int				limiter;
	char			*infile;
	char			**args;
	int				append;
	char			*flag;
	t_envars		*envs;
}	t_cmnds;

// Command Parser.

void		ft_check_quotes(char c, int *inside_s_quote, int *inside_d_quote);
void		ft_init_commands(char *str, t_cmnds **commands, t_envars *envs);
t_cmnds		*ft_command_new(char *str, t_envars *envs);
t_cmnds		**ft_parse_input(char *str, t_envars *envs);
void		ft_commands_clear(t_cmnds **commands_list);

char		*ft_strip_quotes(char *str, int *index, char quote, t_envars *envs);
char		*ft_replace_path(char *str, int *index, t_envars *envs);
void		ft_get_command_outfile(char *line, t_cmnds *command);
void		ft_get_command_infile(char *line, t_cmnds *command);
char		*ft_remove_redirects(char *str);
char		*ft_remove_spaces(char *str);


// Environment Variables Parser.

void		ft_envar_add_back(t_envars **vars, t_envars *new_var);
void		ft_envar_del_one(t_envars **vars, char *key);
t_envars	*ft_envar_new(char *key, char *value);
void		ft_envars_clear(t_envars **vars);
void		ft_print_envars(t_envars *vars);
t_envars	*ft_init_envars(char **envp);

// Readline and prompt.

void		add_line_to_history(char *line);
void		set_prompt(t_envars **envs);
char		*read_prompt_line(void);
void 		rl_replace_line(const char *text, int clear_undo);

// Utilities.

void		fatal_error(char *msg);

// Signals.

void		catch_signals(void);

// Built-ins.
void 		built_ins(t_envars **list, t_cmnds *store);
void 		execute_pwd(void);
void		execute_env(t_envars *list);
void 		execute_unset(t_envars **list, char *key);
void		execute_exit(void);
void 		execute_cd(t_envars **list, t_cmnds **commands);
void 		execute_echo(t_cmnds *commands);

#endif