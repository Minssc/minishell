/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 22:24:00 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/07 00:27:48 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO 대소문자 구분 해야하나?

static t_token	*next_cmd(t_token *tok)
{
	while (tok)
	{
		if (token_ident(tok) == T_CMD && !(tok->type & (REDIR)))
			return (tok);
		tok = tok->next;
	}
	return (0);
}

static int	is_builtin(char *bin)
{
	if (ft_strcmp(bin, "cd") == 0)
		return (B_CD);
	else if (ft_strcmp(bin, "echo") == 0)
		return (B_ECHO);
	else if (ft_strcmp(bin, "env") == 0)
		return (B_ENV);
	else if (ft_strcmp(bin, "exit") == 0)
		return (B_EXIT);
	else if (ft_strcmp(bin, "export") == 0)
		return (B_EXPT);
	else if (ft_strcmp(bin, "pwd") == 0)
		return (B_PWD);
	else if (ft_strcmp(bin, "unset") == 0)
		return (B_UNST);
	else
		return (0);
}

static int	execute_builtin(t_meta *m, int flag)
{
	int		ret;
	
	ret = 0;
	if (flag == B_CD)
		ret = builtin_cd(m->argv);
	else if (flag == B_ECHO)
		ret = builtin_echo(m->argv);
	else if (flag == B_ENV)
		ret = builtin_env(m->argv);
	else if (flag == B_EXIT)
		builtin_exit(m->argv);
	else if (flag == B_EXPT)
		ret = builtin_export(m->argv);
	else if (flag == B_PWD)
		ret = builtin_pwd();
	else if (flag == B_UNST)
		ret = builtin_unset(m->argv);
	return (ret);
}

static int	execute_bin(t_meta *m)
{
	char	*bin;
	int		ret;

	ret = 0;
	bin = bin_find(m, m->argv[0]);
	if (!bin)
		ret = bin_run(m, m->argv[0]);
	else
		ret = bin_run(m, bin);
	// if (!bin)
	// 	return (1); // TODO MANAGE ERROR CODES. FILE NOT FOUND
	// ret = bin_run(m, bin);
}

static void	exec_cmd(t_meta *m, t_token *tok)
{
	int	bi;

	if (m->stop)
		return ;
	m->stop = 1;
	// if (m->child)
	// 	ft_putstr_fd("child ",STDERR_FILENO);
	// ft_putstr_fd("exec cmd: ", STDERR_FILENO);
	// ft_putendl_fd(tok->str, STDERR_FILENO);
	m->argv = argv_build(tok);
	bi = is_builtin(m->argv[0]);
	if (bi)
		execute_builtin(m, bi);
	else
		execute_bin(m);
	argv_destroy(m);
}
// echo > a
// a 실행 후 echo 실행
// pipe 를 기준으로 후위순회 
// echo test | cat

static void	execute(t_meta *m, t_token *tok)
{
	t_token	*pt;
	t_token	*nt;
	int		piped;

	pt = token_prev_delim(tok);
	nt = token_next_delim(tok);
	piped = 0;
	// ft_putstr_fd("EXECUTE ",STDERR_FILENO);
	// ft_putendl_fd(tok->str, STDERR_FILENO);

	if (pt && (pt->type & (T_RDR | T_APR)))
		redir_r(m, tok, pt->type);
	else if (pt && (pt->type & (T_RDL | T_APL)))
		redir_l(m, tok, pt->type); 
	else if (pt && (pt->type & T_PIP))
		piped = redir_p(m, tok); 
	if (nt && piped != 1)
		execute(m, nt->next);
	if ((!pt || (pt->type & T_PIP)) && piped != 1 && !m->stop)
		exec_cmd(m, tok);
}

void	exec_start(t_meta *m)
{
	t_token	*ct;
	int		stat;

	ct = next_cmd(m->token_start);
	execute(m, ct);
	dup2(m->stdin,STDIN_FILENO);
	dup2(m->stdout,STDOUT_FILENO);
	// printf("%d %d\n",m->fd_out, m->fd_in);
	fd_close(m->fd_out);
	fd_close(m->fd_in);
	waitpid(-1, &stat, 0);
	stat = WEXITSTATUS(stat);
	if (m->child)
		mexit(stat);
	m->stop = 0;
	// ct = next_cmd(m->token_start);
	// execute(m, ct);
	// dup2(m->stdin,STDIN_FILENO);
	// dup2(m->stdout,STDOUT_FILENO);
	// close(m->fd_out);
	// close(m->fd_in);
	// waitpid(-1, &stat, 0);
	// stat = WEXITSTATUS(stat);
	// if (m->child)
	// {
	// 	ft_putendl_fd("EXIT HERE",STDERR_FILENO);
	// 	// printf("exit here\n");
	// 	mexit(stat);
	// }
	// m->stop = 0;
	// ft_putendl_fd("WATSUP!",STDERR_FILENO);
	// ct = next_cmd(m->token_start->next);
	// ct->prev = 0;
	// execute(m, ct);
	// waitpid(-1, &stat, 0);
	// stat = WEXITSTATUS(stat);
	// if (m->child)
	// {
	// 	printf("exit here\n");
	// 	mexit(stat);
	// }
	// while (ct)
	// {
	
		// ct = next_cmd(m->token_start->next);
		// break ;
	// }
}