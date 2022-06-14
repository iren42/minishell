#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"

# define TOO_MANY_ARG "Too many arguments\n"
# define ERR_QUOTE "Error on quote\n"
# define MALLOC "Error on malloc()\n"

# define PROMPT "> "

typedef enum e_token_type
{
	NONE,
	WORD,
	SEMI,
	GREAT,
	LESS,
	DOUBLE_GREAT,
	PIPE, //NEWLINE,
}			t_token_type;

typedef struct	s_token
{
	char	*value;
	t_token_type	type;
	
}	t_token;

typedef struct	s_mini
{
	t_list	*tokens;
	char	*s;
	char	**env;
	int	fd;

} t_mini;

void	print_tmini(t_mini *mini);
void	print_split(char **split);
void	print_lst(t_list *head);

t_list	*lexer(t_mini *m);
int	is_quote(int c);
int	ft_isspace(int c);
void	del_token(void *token);


//char	**ft_splitsh(const char *s, const char *c);
void	ft_error(char *m, int code);

t_list	*parser(t_mini *m);
#endif
