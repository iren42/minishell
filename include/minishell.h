#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"

# define PROMPT "> "
typedef struct	s_token
{
	char	*cmd;
	char	*opt;
}	t_token;

typedef struct	s_mini
{
	t_token	*tokens;
	char	*s;
	char	**env;
	int	fd;

} t_mini;

void	print_tmini(t_mini *mini);
void	lexer(t_mini *m);

#endif
