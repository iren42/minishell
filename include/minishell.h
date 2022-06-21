#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include "libft.h"

# define TOO_MANY_ARG "Too many arguments\n"
# define ERR_QUOTE "Error on quote\n"
# define MALLOC "Error on malloc()\n"

# define PROMPT "> "

# define SUCCESS 1
# define FAILURE 0

# define GRN "\x1B[32m"
# define RESET "\x1B[0m"
# define YEL "\x1B[33m"
# define BLU "\x1B[34m"
# define PUR "\x1B[35m"
struct s_mini;
typedef enum e_token_type
{
	NONE,
	WORD,
	SEMI,
	GREAT,
	LESS,
	DOUBLE_GREAT,
	PIPE,
	NL,
}	t_token_type;

typedef struct	s_token
{
	char	*value;
	t_token_type	type;
	struct s_mini	*m;
	
}	t_token;

typedef enum e_redir_type{
	RE_GREAT,
	RE_DOUBLE_GREAT,
	RE_LESS,
}	t_redir_type;

typedef struct s_redir
{
	int				index;
	t_redir_type	type;
	int				is_in_quotes;
	char			*filename;
}	t_redir;

typedef struct s_arg{
	int				is_in_quotes;
	char			*value;
}	t_arg;

typedef struct	s_cmdtab
{
	int			is_in_quotes;
	char		*cmd;
	t_list		*arg_list;
	t_list		*redir_list;
	struct s_mini	*m;
} t_cmdtab;

typedef struct	s_mini
{
	t_list	*token_list;
	t_list	*cmdtab_list;
	t_list	*env_list;
	char	*s;
	char	**env;
	int	fd;

} t_mini;

typedef struct s_env
{
//	int	is_in_quotes;
	int	index;
	char	*name;
	char	*value;
} t_env;

typedef struct s_quote
{
	char	c;
	int	index;

} t_quote;
typedef struct s_func_cmd_sub
{
	t_list	*env_list;
	t_list	*quote_list;
	char	*res;
	char	*tenv_value;
	int	list_index;
	int	start;
	int	end;
	char	q;
} t_func_cmd_sub;


void	print_tmini(t_mini *mini);
void	print_split(char **split);
void	print_list(t_list *head, void (*f)(void *));
//void	print_token(t_token *t);
void	print_cmdtab(void *o);
void	print_token(void *t);
void	print_env(void *e);

t_list	*lexer(t_mini *m);
int	is_quote(int c);
int	ft_isspace(int c);
void	del_token(void *token);


//char	**ft_splitsh(const char *s, const char *c);
void	ft_error(char *m, int code);

t_list	*parser(t_mini *m);
char	*get_cmd(t_list *env_list, char *cmd);
void	free_split(char **split);
void	del_cmdtab(void *o);

char	*expander(t_mini *m);
//t_list	*create_list(char *s);
char	*var_substitution(t_list *export_list, char *s);
char	*rm_superflous(char *s);
int	matching(char b1, char b2);
char	get_char(void *o);
void	del_tfunc_rm_quotes(void *o);
int	get_index(void *o);
void	push(t_list **l, char c, char *s, int i);
void	del_env(void *o);


void	signal_handler();
void	print_prompt();

int	ft_pwd(t_cmdtab *c);
int	ft_env(t_cmdtab *c);
int	ft_export(t_cmdtab *c);
char	*get_env_name(void *o);
char	*get_env_value(void *o);
int	get_len_env_name(char *env);
int	is_syntax_ok(char *s);
int	ft_unset(t_cmdtab *c);
char	*get_arg_value(void *o);

#endif
