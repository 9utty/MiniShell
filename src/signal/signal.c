/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gulee <gulee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 14:28:53 by gulee             #+#    #+#             */
/*   Updated: 2022/09/14 14:51:00 by gulee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief readline 을 받는동안 SIGINT를 시그널 처리하는 함수
 *
 * @param sig - 함수 호출을 한 signal의 번호
 */
static void	ctrl_c_inside_loop(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("\0", 0);
	rl_on_new_line();
	rl_redisplay();
	get_global_data()->exitcode = 1;
}

/**
 * @brief - SIGINT 및 SIGQUIT 신호를 처리하는 시그널
			종료 상태를 130 또는 131로 설정
 *
 * @param sig - 함수 호출을 한 signal의 번호
 */
void	exec_sig_handler(int sig)
{
	if (sig == SIGINT)
		get_global_data()->exitcode = 130;
	else if (sig == SIGQUIT)
		get_global_data()->exitcode = 131;
}

/**
 * @brief - SIGTERM 시그널과 함께 kill을 사용하여
 * 			프로세스를 읽고 쓰는 시그널을 heredoc에 보낸다
 *
 * @param sig - 함수를 호출한 signal의 번호
 */
void	hdoc_handler(int sig)
{
	(void) sig;
	printf("\n");
	kill(get_global_data()->hdoc_pid, SIGTERM);
	get_global_data()->hdoc_break = TRUE_E;
	get_global_data()->exitcode = 130;
}

/**
 * @brief - SIGINT로 재설정하고 SIGQUIT를 무시하고,
 * 			시그날이 터미널에 출력되지 않게 하는 함수
 *
 */
void	init_signals(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &t);
	signal(SIGINT, ctrl_c_inside_loop);
	signal(SIGQUIT, SIG_IGN);
}
