#ifndef MINISHELL_STRUCT_H
#define MINISHELL_STRUCT_H
struct s_mini;
typedef enum e_token_type
{
	NONE, // 0
	WORD,
	GREAT, // 2
	LESS,
	DOUBLE_GREAT , //4
	DOUBLE_LESS,
	PIPE, //6
	NL, // 7
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

typedef enum e_cmd_type{
	PWD, // 0
	ECHO,
	CD, //2
	EXPORT,
	UNSET, //4
	ENV,
	EXIT, // 6
	OTHER, //7
}	t_cmd_type;

typedef struct	s_cmdtab
{
	int			is_in_quotes;
	char		*cmd;
	t_list		*arg_list;
	t_list		*redir_list;
	struct s_mini	*m;
	t_cmd_type	type;
} t_cmdtab;

typedef struct	s_mini
{
	t_list	*token_list;
	t_list	*cmdtab_list;
	t_list	*env_list;
	char	**split_builtin;
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

typedef struct s_exec
{
	char	**split_env;
	int		nb_cmd;
//	pid_t	*pids;
//	int		**ends;
//	int		err;
	t_mini	*m;
	t_list	*cmdtabl;
	int	redir_fd[2];

} t_exec;
#endif
