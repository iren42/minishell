#ifndef MINISHELL_STRUCT_H
#define MINISHELL_STRUCT_H
struct s_mini;
typedef enum e_token_type
{
	NONE,
	WORD,
	SEMI,
	GREAT,
	LESS,
	DOUBLE_GREAT,
	DOUBLE_LESS,
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
	RE_DOUBLE_LESS,
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
#endif
