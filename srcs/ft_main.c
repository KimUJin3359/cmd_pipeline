/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojikim <woojikim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 21:46:05 by woojikim          #+#    #+#             */
/*   Updated: 2021/06/12 21:52:52 by woojikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_h.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int		main(int ac, char *av[])
{
	t_cmd	cmd;
	int		pipe_fd[2];
	int		status;
	pid_t	pid;

	if (ac != 5 || pipe(pipe_fd) < 0 || (pid = fork()) < 0)
		exit(1);
	if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == -1)
			exit(1);
		if (!WIFEXITED(status))
			exit(1);
		if (redirect_output(av[4]) || connect_pipe(pipe_fd, STDIN_FILENO))
			exit(1);
		run_cmd(&cmd, av[3]);
	}
	else if (pid == 0)
	{
		if (redirect_input(av[1]) || connect_pipe(pipe_fd, STDOUT_FILENO))
			exit(1);
		run_cmd(&cmd, av[2]);
	}
	return (0);
}
