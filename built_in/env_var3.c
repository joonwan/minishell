/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunhwang <eunhwang@student.42gyeongsan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:01:52 by eunhwang          #+#    #+#             */
/*   Updated: 2024/08/03 17:32:45 by eunhwang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "built_in.h"

int	include_plus(char *s)
{
	int	i;

	i = 0;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == '+')
			return (i);
		i++;
	}
	return (-1);
}

void	change_value(t_env_list *lst, char *key, char *value)
{
	char		*key_equal;
	t_env_node	*tmp_node;

	tmp_node = find_node(lst, key);
	key_equal = ft_substr(tmp_node -> content, 0, \
		include_equal(tmp_node -> content) + 1);
	free(tmp_node -> content);
	tmp_node -> content = ft_strjoin(key_equal, value);
	free(key_equal);
}

void	join_value(t_env_list *lst, char *key, char *value)
{
	t_env_node	*tmp_node;
	char		*rm_content;

	tmp_node = find_node(lst, key);
	if (include_equal(tmp_node -> content) == -1)
	{
		rm_content = ft_strjoin(tmp_node -> content, "=");
		free(tmp_node -> content);
		tmp_node -> content = ft_strjoin(rm_content, value);
		free(rm_content);
	}
	else
	{
		rm_content = tmp_node -> content;
		tmp_node -> content = ft_strjoin(tmp_node -> content, value);
		free(rm_content);
	}
}

int	validate_key(char *key)
{
	int	i;

	i = 0;
	if (*key >= '0' && *key <= '9')
		return (-1);
	while (*(key + i) != '\0')
	{
		if (ft_isalnum(*(key + i)) == 0 && *(key + i) != '_')
			return (-1);
		i++;
	}
	return (0);
}

void	not_valid_identifier(char *s)
{
	write(1, "porschell: export: `", 16);
	write(1, s, ft_strlen(s));
	write(1, "\': not a valid identifier\n", 27);
}
