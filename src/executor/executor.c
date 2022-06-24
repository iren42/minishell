/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gufestin <gufestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 21:28:08 by gufestin          #+#    #+#             */
/*   Updated: 2022/06/24 06:50:29 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_error(t_redir *redir, t_exec *e)
{
	struct stat		buf;

	if (stat(redir->filename, &buf) == 0)
	{
		if (buf.st_mode & S_IFDIR)
		{
			print_error("shell", redir->filename, 0, "Is a directory");
			return (1);
		}
		else if ((buf.st_mode & S_IXUSR) == 0)
		{
			print_error("shell", redir->filename, 0, "Permission denied");
			return (1);
		}
	}
	print_error("shell", redir->filename, 0, "No such file or directory");
	return (1);
}


int	ex_infile(t_exec *e, int fd_in, int child, int **fd)
{
	t_list	*tmp;

	if (child > 0)
	{
		fd_in = fd[child - 1][IN];
		close(fd[child - 1][OUT]);
	}
	tmp = ((t_cmdtab *)(e->cmdtabl->content))->redir_list;
	//	tmp = (ex_get_cmd_child(cmd, child))->infile;
	while (tmp)
	{
		if (fd_in != STDIN)
			close(fd_in);
		if (get_redir_type(tmp->content) == RE_LESS)
		{
			//	fd_in = open(&(tmp->content[2]), O_RDONLY);
			fd_in = open(((t_redir *)(tmp->content))->filename, O_RDONLY);
		}
		else if (get_redir_type(tmp->content) == RE_DOUBLE_LESS)
		{
			printf("eof = %s\n", ((t_redir *)(tmp->content))->filename);
			fd_in = ft_heredoc(((t_redir *)(tmp->content))->filename);
		}
		if (fd_in < 0)
		{
			//			error_handler(e_file);
			redir_error(tmp->content, e);
			exit(1);
		}
		tmp = tmp->next;
	}
	return (fd_in);// return le dernier infile ouvert
}

int	ex_outfile(t_exec *e, int fd_out, int child, int **fd)
{
	t_list	*tp;

	if (child != e->nb_cmd - 1)
	{
		fd_out = fd[child][WRITE];
		close(fd[child][READ]);
	}
	tp = ((t_cmdtab *)(e->cmdtabl->content))->redir_list;
	while (tp)
	{
		if (fd_out != STDOUT)
			close(fd_out);
		if (get_redir_type(tp->content) == RE_GREAT)
			fd_out = open(((t_redir *)(tp->content))->filename, O_CREAT | O_RDWR | O_TRUNC,  0664);
		else if (get_redir_type(tp->content) == RE_DOUBLE_GREAT)
			fd_out = open(((t_redir *)(tp->content))->filename, O_CREAT | O_RDWR | O_APPEND, 0664);
		if (fd_out < 0)
		{
			redir_error(tp->content, e);
			exit(1);
		}
		tp = tp->next;
	}
	return (fd_out);
}

char	**ft_split_cmd(t_mini *mini, int cmd_num)
{
	char	**split_cmd;
	int		i;
	t_list	*tmp_arg_list;
	int	size;
	t_list	*tmp_cmdtab_list;

	tmp_cmdtab_list = mini->cmdtab_list;
	i = 0;
	while (i < cmd_num)
	{
		tmp_cmdtab_list = tmp_cmdtab_list->next;
		i++;
	}
	size = ft_lstsize(((t_cmdtab *)(tmp_cmdtab_list->content))->arg_list);
	split_cmd = (char **)malloc(sizeof(char *) * (size + 2));
	if (!split_cmd)
		exit(1); // malloc error
	//	printf("split cmd 0 %s\n",ft_strdup(((t_cmdtab *)(tmp_cmdtab_list->content))->cmd));
	split_cmd[0] = 0;
	if (((t_cmdtab *)(tmp_cmdtab_list->content))->cmd)
		split_cmd[0] = ft_strdup(((t_cmdtab *)(tmp_cmdtab_list->content))->cmd);
	if (!split_cmd[0])
		exit(1); // malloc error
	//	split_cmd[0] = ft_strdup("ls");
	tmp_arg_list = ((t_cmdtab *)(tmp_cmdtab_list->content))->arg_list;
	i = 1;
	while (i - 1 < size)
	{
		split_cmd[i] = ft_strdup(((t_arg *)(tmp_arg_list->content))->value);
		if (!split_cmd[i])
			exit(1); // malloc error
		i++;
		tmp_arg_list = tmp_arg_list->next;
	}
	split_cmd[i] = NULL;
	return (split_cmd);
}

char	**ft_split_env(t_mini *mini)
{
	char	**split_env;
	int		i;
	t_list	*tmp_list;
	int		size;
	char	*tmp;

	size = ft_lstsize(mini->env_list);
	split_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!split_env)
		exit(1); // malloc error
	i = 0;
	tmp_list = mini->env_list;
	while (i < size)
	{
		split_env[i] = ft_strjoin(((t_env *)(tmp_list->content))->name, "=");
		if (!split_env[i])
			exit(1); // malloc error
		tmp = split_env[i];
		split_env[i] = ft_strjoin(split_env[i], ((t_env *)(tmp_list->content))->value);
		//		if (!split_env[i])
		//			exit(1); // malloc error
		free(tmp);
		i++;
		tmp_list = tmp_list->next;
	}
	split_env[i] = NULL;
	return (split_env);
}

void	ft_execve(t_cmdtab *cmdtab, char **split_cmd, char **split_env)
{
	execve(cmdtab->cmd, split_cmd, split_env);
}

static int	ft_wait(pid_t *pids, int n)
{
	int	status;
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (i < n)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		err = WEXITSTATUS(status);
	return (err);
}

char	*is_builtin(char *cmd, t_mini *m) // renvoie un ptr sur split_builtin
{
	int	i;

	i = 0;
	if (m->split_builtin)
	{
		while (m->split_builtin[i])
		{
			if (ft_memcmp(cmd, m->split_builtin[i], ft_strlen(cmd) + 1) == 0)
				return (m->split_builtin[i]);
			i++;
		}
	}
	return (0);
}

void	execute_cmd(char **split_cmd, char *cmd, t_cmdtab *c, t_exec *e)
{
//	printf("cmd type %d\n", c->type);
	if (c->type == EXPORT)
		ft_export(c);
	else if (c->type == UNSET)
		ft_unset(c);
	else if (c->type == CD)
		ft_cd(c);
	else if (c->type == ECHO)
	{
//		ft_putstr_fd("echo built\n", 2);
		ft_echo(c);
	}
	else if (c->type == ENV)
		ft_env(c);
	else if (c->type == PWD)
		ft_pwd(c);
	else if (c->type == EXIT)
		ft_exit(c);
	else
		ft_execve((t_cmdtab *)(e->cmdtabl->content), split_cmd, e->split_env);
}

void	exec_child(t_exec *e, int **ends, char **split_cmd, int i)
{
	char	*p;
	int	fd_in;
	int	fd_out;

	fd_in = ex_infile(e, STDIN, i, ends);

	if (fd_in != STDIN )
	{
		dup2(fd_in, STDIN);
		close(fd_in);
	}
	fd_out = ex_outfile(e, STDOUT, i, ends);

	if (fd_out != STDOUT )
	{
		dup2(fd_out, STDOUT);
		close(fd_out);
	}
	p = is_builtin(split_cmd[0], e->m);
	close_all_pipes(ends, e->nb_cmd);
	printf("in exec child\n");
	execute_cmd(split_cmd, p, e->cmdtabl->content, e);
	exit(0);
	printf("after exec child\n");

}

void	exec_cmdtab_list(t_exec *e, pid_t *pids, int **ends)
{
	int		i;
	char	**split_cmd;
	i = 0;
	while (i < e->nb_cmd)
	{
		split_cmd = ft_split_cmd(e->m, i);
		//		print_split(split_cmd);
		pids[i] = fork();
		if (pids[i] == -1)
			exit(1); // fork error
		if (pids[i] == 0) // child
		{
			printf("inside child %d\n", i);
			exec_child(e, ends, split_cmd, i);
		}
		e->cmdtabl = e->cmdtabl->next;
		free_split(split_cmd);
		i++;
		printf("i %d is done\n", i);
	}
}

void	*init_t_exec(t_exec *e, t_mini *m)
{
	e->split_env = ft_split_env(m);
	e->nb_cmd = ft_lstsize(m->cmdtab_list);
	e->cmdtabl = m->cmdtab_list;
	e->m = m;
	if (!e->split_env || !e->cmdtabl)
		exit(1);
}

void	exec_no_fork(t_exec *e, t_cmdtab *ptr)
{
	char	**split_cmd;

	split_cmd = ft_split_cmd(e->m, 0);
	//	print_split(split_cmd);
	execute_cmd(split_cmd, ptr->cmd, ptr, e);
	free_split(split_cmd);
}

int	executor(t_mini *mini)
{
	pid_t	*pids;
	int		**ends; // pipes
	int		err;
	t_exec	e;
	int	child;
	int	status;
	t_cmdtab	*ptr;

	printf("--IN EXECUTOR----\n");
	if ((t_list *)(mini->cmdtab_list) == NULL)
		return (0); // cmd =(null)
	ptr = get_cmdtab_ptr(mini->cmdtab_list->content);
	init_t_exec(&e, mini);
	if (e.nb_cmd == 1 && (ptr->type == CD || ptr->type == UNSET
				|| ptr->type == EXPORT || ptr->type == EXIT))
		exec_no_fork(&e, ptr);
	else
	{
		printf("execution of a command line with pipes\n");
		pids = malloc(sizeof(pid_t) * e.nb_cmd);
		if (!pids)
			exit(1); // malloc error
		ends = init_pipes(e.nb_cmd);
		open_pipes(ends, e.nb_cmd);
		printf("pipes are ready\n");
		exec_cmdtab_list(&e, pids, ends);
		close_all_pipes(ends, e.nb_cmd);
		err = ft_wait(pids, e.nb_cmd);

		free_pipes(ends, e.nb_cmd);
		free(pids);
	}
	free_split(e.split_env);
	printf("--IN EXECUTOR END----\n");
	return (err);
}
