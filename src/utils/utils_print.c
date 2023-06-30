/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 23:04:20 by gulee             #+#    #+#             */
/*   Updated: 2022/09/10 20:21:59 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_env *print)
{
	while (print != 0)
	{
		printf("%s\n", print ->str);
		print = print ->next;
	}
	printf("\n");
}

void	print_arr(char **print)
{
	int	index;

	index = 0;
	printf("\033[1;34min Arguments:\033[0m\n");
	if (print == NULL)
		return ;
	while (print[index] != NULL)
	{
		printf("-%s-\n", print[index]);
		index++;
	}
}

void	print_cmd(t_node *node)
{
	if (!node)
		printf("\033[1;32mList is empty!\033[31m\n");
	while (node)
	{
		printf("\033[1;36m===== node =====\033[31m\n");
		if (node->type == INFILE_E)
			printf("Type: Infile\n");
		else if (node->type == AMBIGU_E)
			printf("Type: Ambiguous\n");
		else if (node->type == APPEND_E)
			printf("Type: Append\n");
		else if (node->type == TRUNC_E)
			printf("Type: Trunicate\n");
		else if (node->type == PIPE_E)
			printf("Type: Pipe \n");
		else if (node->type == TOSTDOUT_E)
			printf("Type: std out\n");
		else if (node->type == HDOCSPACE_E)
			printf("Type: Heredoc space\n");
		else if (node->type == HDOCQUOTE_E)
			printf("Type: Heredoc quote\n");
		print_arr(node->arg);
		node = node->next;
	}
}
