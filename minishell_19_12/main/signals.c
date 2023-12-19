/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/10/06 15:25:53 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		e_signal = 130;
	}
}

void	signals_here_doc(int sign)
{
	if (sign == SIGQUIT)
		SIG_IGN ;
	else if (sign == SIGINT)
	{
		write(2, "\n", 1);
		exit(1);
	}
}

void    set_signals(void)
{
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
}
