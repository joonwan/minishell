/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:50:00 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/03 16:50:02 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	is_buitin(char *p_name)
{
	if (ft_strncmp("echo", p_name, get_content_len(p_name)) == 0 \
		&& (get_content_len("echo") == get_content_len(p_name)))
		return (ECHO);
	if (ft_strncmp("cd", p_name, get_content_len(p_name)) == 0 \
		&& (get_content_len("cd") == get_content_len(p_name)))
		return (CD);
	if (ft_strncmp("pwd", p_name, get_content_len(p_name)) == 0 \
		&& (get_content_len("pwd") == get_content_len(p_name)))
		return (PWD);
	if (ft_strncmp("export", p_name, get_content_len(p_name)) == 0 \
		&& (get_content_len("export") == get_content_len(p_name)))
		return (EXPORT);
	if (ft_strncmp("unset", p_name, get_content_len(p_name)) == 0 \
		&& (get_content_len("unset") == get_content_len(p_name)))
		return (UNSET);
	if (ft_strncmp("env", p_name, get_content_len(p_name)) == 0 \
		&& (get_content_len("env") == get_content_len(p_name)))
		return (ENV);
	if (ft_strncmp("exit", p_name, get_content_len(p_name)) == 0 \
		&& (get_content_len("exit") == get_content_len(p_name)))
		return (EXIT);
	return (-1);
}

void	run_built_in(t_process_info *process, t_env_list *el, int is_single_cmd)
{
	int	argc;
	int	type;

	argc = get_argc(process -> argv);
	type = is_buitin(process -> program_name);
	if (type == ECHO)
		echo(argc, process -> argv);
	if (type == CD)
		cd(argc, process -> argv, el);
	if (type == PWD)
		pwd(el);
	if (type == EXPORT)
		export(argc, el, process -> argv);
	if (type == UNSET)
		unset(argc, process -> argv, el);
	if (type == ENV)
		env(el);
	if (type == EXIT && is_single_cmd)
	{
		write(1, "exit\n", 5);
		bi_exit(argc, process -> argv);
	}
	else if (type == EXIT && !is_single_cmd)
		bi_exit(argc, process -> argv);
}

void	excute_built_in(t_process_info *process, pid_t pids[], t_env_list *el)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	signal(SIGQUIT, sigquit_in_process);
	signal(SIGINT, sigint_in_process);
	pids[process -> idx] = pid;
	if (pid == 0)
	{
		close(fd[0]);
		if (process -> next)
			(dup2(fd[1], STDOUT_FILENO), close(fd[1]));
		if (process -> is_redirected)
			set_stream(process -> in, process -> out);
		run_built_in(process, el, 0);
		exit(0);
	}
	else
		(close(fd[1]), dup2(fd[0], STDIN_FILENO), close(fd[0]));
}
