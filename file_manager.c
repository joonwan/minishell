/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonwan <joonwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:50:17 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/06 16:01:53 by joonwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_input_file(t_q_token *now)
{
	int	fd;

	fd = open(now -> content, O_RDONLY);
	if (fd == -1)
	{
		handle_file_open_error(now -> content);
		return (0);
	}
	now -> fd = fd;
	return (1);
}

int	openfile(t_q_token *prev, t_q_token *now)
{
	enum e_q_token_type	type;
	int					fd;

	type = prev -> type;
	if (type == RDRT_AO || type == RDRT_TO)
	{
		if (type == RDRT_AO)
			fd = open(now -> content, \
				O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			fd = open(now -> content, \
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd == -1)
		{
			handle_file_create_error(now -> content);
			return (0);
		}
		now -> fd = fd;
	}
	if (type == RDRT_IN)
		return (open_input_file(now));
	return (1);
}

int	open_files(t_q_token_list *list)
{
	t_q_token	*now;
	t_q_token	*prev;

	prev = NULL;
	now = list -> head;
	while (now)
	{
		if (now -> type == FILE_C)
		{
			if (!openfile(prev, now))
			{
				clear_q_token_list(list);
				return (0);
			}
		}
		if (now -> type == DELI)
		{
			if (!handle_heredoc(list, now))
				return (0);
		}
		prev = now;
		now = now -> next;
	}
	return (1);
}
