/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 02:27:32 by joojeon           #+#    #+#             */
/*   Updated: 2024/07/30 16:45:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	clear_process(t_process_info *process)
{
	free(process -> argv);
	free(process);
}

void	clear_process_list(t_process_list *list)
{
	t_process_info	*process;
	t_process_info	*tmp;

	process = list -> head;
	while (process)
	{
		tmp = process -> next;
		clear_process(process);
		process = tmp;
	}
	free(list);
}
