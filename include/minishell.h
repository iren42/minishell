/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:42:57 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/25 05:22:05 by gufestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "libft.h"
# include "minishell_struct.h"

extern int	g_errno;

# define TOO_MANY_ARG "Too many arguments\n"
# define ERR_QUOTE "Error on quote\n"
# define MALLOC "Error on malloc()\n"

# define GRN "\x1B[32m"
# define RESET "\x1B[0m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define PUR "\x1B[35m"
# define PROMPT "minishell$ "
//#define PROMPT "> "

# define SUCCESS 1
# define FAILURE 0
# define STDERR 2
# define STDIN 0
# define STDOUT 1

# define OUT 1
# define IN 0
# define WRITE 1
# define READ 0
# define BUF_SIZE 254

void			print_tmini(t_mini *mini);
void			print_split(char **split);
void			print_list(t_list *head, void (*f)(void *));
void			print_cmdtab(void *o);
void			print_token(void *t);
void			print_env(void *e);
void			print_quote(void *e);
void			print_arg(void *o);

// IN EXECUTOR
int				executor(t_mini *mini);
int				**init_pipes(int n);
void			open_pipes(int **fd, int n);
void			free_pipes(int **ends, int n);
void			close_all_pipes(int **ends, int n);
void			close_all_pipes_but_index(int **ends, int n, int index);
//void			executor_pipes(t_executor_variables *var);
void			exec_cmdtab_list(t_exec *e, pid_t *pids, int **ends);

int				ft_heredoc(char *eof);

// IN PARSER
int				lexer(t_mini *m);
t_list			*parser(t_mini *m);
void			fill_cmd(t_token *t, t_cmdtab *ct, int *ret);
void			fill_args(t_token *t, t_cmdtab *c, int *ret);
void			fill_redir(t_token *t, t_cmdtab *c);
t_token			*create_token(char *p, int *to_set, t_mini *m);
t_token			*token_word(char *p, int *to_set, t_mini *m);
t_token			*token_pipe_nl(char *p, int *to_set, t_mini *m);
t_token			*token_great_less(char *p, int *to_set, t_mini *m);
t_token			*token_double_great_less(char *p, int *to_set, t_mini *m);
int				check_syntax_token(t_list *tokens);
int				calc_len_word(int *len, int *start, char *p, t_token *t);

void			ft_error(char *m, int code);
void			print_error(char *where, char *file, int err, char *msg);

// IN EXPANDER
int				expander(t_mini *m);
char			*var_substitution(t_list *export_list, char *s);
char			*rm_superflous(char *s);
int				are_quotes_closed(char *s);
void			push(t_list **l, char c, int i);
int				check_if_substitution(char *s, t_func_cmd_sub *f);
int				len_word(char *s);
void			sub_dollar(t_func_cmd_sub *f, int *i, char *s);
char			*join_regular_str(t_func_cmd_sub *f, int i, char *s);
void			sub_for_quotes(t_func_cmd_sub *f, int *i, char *s);

void			signal_handler(void);
void			signal_handler_child(void);
void			print_prompt(void);
void			print_prompt_child(void);

// IN BUILTIN
int				ft_pwd(void);
int				ft_env(t_cmdtab *c);
int				ft_export(t_cmdtab *c);
int				ft_unset(t_cmdtab *c);
int				ft_exit(t_cmdtab *c);
int				ft_cd(t_cmdtab *c);
int				ft_echo(t_cmdtab *c);

// IN UTIL
void			del_arg(void *o);
char			*get_arg_value(void *o);

char			*get_env_name(void *o);
char			*get_env_value(void *o);
int				get_len_env_name(char *env);
void			del_env(void *o);
char			*ft_getenv(char *name, t_list *env_list);
t_env			*ft_getenv_ptr(char *name, t_list *env_list);
t_env			*create_new_env(char *name, char *value);
t_env			*create_tenv(t_arg *a);

char			get_quote_char(void *o);
void			del_quote(void *o);
int				get_quote_index(void *o);

void			del_token(void *token);
char			*get_token_value(t_token *t);
int				get_token_type(t_token *t);

void			del_cmdtab(void *o);
t_cmdtab		*get_cmdtab_ptr(void *o);

void			del_redir(void *o);
t_redir_type	get_redir_type(t_redir *r);

int				is_quote(char c);
int				ft_isspace(char c);
int				is_spe_char(char c);

int				is_syntax_ok(char *s);
int				matching(char b1, char b2);
char			*get_cmd(t_list *env_list, char *cmd);
void			free_split(char **split);

char			*ft_readline(void);
int				clear_exit(t_mini mini);
void			call_and_clear(t_mini *mini);

int				ex_infile(t_exec *e, int fd_in);
int				ex_outfile(t_exec *e, int fd_out);

char			**ft_split_env(t_mini *mini);
char			**ft_split_cmd(t_mini *mini, int cmd_num);

int				ft_wait(pid_t *pids, int n);
int				redir_error(t_redir *redir);
char			*is_builtin(char *cmd, t_mini *m);
void			init_t_exec(t_exec *e, t_mini *m);

void			exec_child(t_exec *e, int **ends, char **split_cmd, int i);

void			execute_cmd(char **split_cmd, t_cmdtab *c, t_exec *e);

#endif
