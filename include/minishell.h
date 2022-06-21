#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>

#include "libft.h"
#include "minishell_struct.h"

#define TOO_MANY_ARG "Too many arguments\n"
#define ERR_QUOTE "Error on quote\n"
#define MALLOC "Error on malloc()\n"

#define PROMPT "> "

#define SUCCESS 1
#define FAILURE 0
#define STDERR 2
#define STDIN 1

#define BUF_SIZE 254

#define GRN "\x1B[32m"
#define RESET "\x1B[0m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define PUR "\x1B[35m"

void	print_tmini(t_mini *mini);
void print_split(char **split);
void print_list(t_list *head, void (*f)(void *));
void print_cmdtab(void *o);
void print_token(void *t);
void print_env(void *e);

// IN PARSER
t_list *lexer(t_mini *m);
t_list *parser(t_mini *m);

void ft_error(char *m, int code);
void print_error(char *where, char *file, int err, char *msg);

// IN EXPANDER
char *expander(t_mini *m);
char *var_substitution(t_list *export_list, char *s);
char *rm_superflous(char *s);
void push(t_list **l, char c, char *s, int i);

void signal_handler();
void print_prompt();

// IN BUILTIN
int ft_pwd(t_cmdtab *c);
int ft_env(t_cmdtab *c);
int ft_export(t_cmdtab *c);
int ft_unset(t_cmdtab *c);
int ft_exit(t_cmdtab *c);
int ft_cd(t_cmdtab *c);
int ft_echo(t_cmdtab *c);


// IN UTIL
void del_arg(void *o);
char *get_arg_value(void *o);

char *get_env_name(void *o);
char *get_env_value(void *o);
int get_len_env_name(char *env);
void del_env(void *o);
char *ft_getenv(char *name, t_list *env_list);

char get_quote_char(void *o);
void del_quote(void *o);
int get_quote_index(void *o);

void del_token(void *token);
char	*get_token_value(t_token *t);
int	get_token_type(t_token *t);

void del_cmdtab(void *o);

void	del_redir(void *o);

int is_quote(char c);
int ft_isspace(char c);
int	is_spe_char(char c);

int is_syntax_ok(char *s);
int matching(char b1, char b2);
char *get_cmd(t_list *env_list, char *cmd);
void free_split(char **split);
int	number_of_args(t_list *al);

#endif
