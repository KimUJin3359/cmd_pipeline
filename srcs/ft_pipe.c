/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woojikim <woojikim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 21:49:41 by woojikim          #+#    #+#             */
/*   Updated: 2021/06/12 21:55:55 by woojikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_h.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int		redirect_input(const char *file)
{
	int fd;
	int res;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error(0, file);
		return (1);
	}
	res = dup2(fd, STDIN_FILENO);
	close(fd);
	if (res == -1)
		return (1);
	return (0);
}

int		redirect_output(const char *file)
{
	int fd;
	int res;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		print_error(0, file);
		return (1);
	}
	res = dup2(fd, STDOUT_FILENO);
	close(fd);
	if (res == -1)
		return (1);
	return (0);
}

int		connect_pipe(int pipe_fd[2], int stdio)
{
	int res;

	res = dup2(pipe_fd[stdio], stdio);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	if (res == -1)
		return (1);
	return (0);
}

void	split_cmd(t_cmd *cmd, const char *argv)
{
	char **word;

	word = ft_split(argv, ' ');
	cmd->cmd = ft_strdup(word[0]);
	cmd->file[0] = ft_strjoin("/bin/", word[0]);
	cmd->file[1] = ft_strjoin("/usr/bin/", word[0]);
	cmd->file[2] = ft_strjoin("/usr/local/bin/", word[0]);
	cmd->file[3] = ft_strjoin("/sbin/", word[0]);
	cmd->file[4] = ft_strjoin("/usr/sbin/", word[0]);
	cmd->argv = (char *const *)word;
	cmd->envp = NULL;
}

void	run_cmd(t_cmd *cmd, const char *argv)
{
	int		i;

	i = 0;
	split_cmd(cmd, argv);
	while (i < 5)
		execve(cmd->file[i++], cmd->argv, cmd->envp);
	i = 0;
	while (i < 5)
		free(cmd->file[i++]);
	i = 0;
	while (cmd->argv[i])
		free(cmd->argv[i]);
	free((void *)cmd->argv);
	print_error(1, cmd->cmd);
}
