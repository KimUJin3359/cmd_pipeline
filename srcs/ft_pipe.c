#include "ft_h.h"
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	redirect_input(const char *file)
{
	int fd;
	int res;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		return (1);
	}
	res = dup2(fd, STDIN_FILENO);
	close(fd);
	if (res == -1)
		return (1);
	return (0);
}

int	redirect_output(const char *file)
{
	int fd;
	int res;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror(file);
		return (1);
	}
	res = dup2(fd, STDOUT_FILENO);
	close(fd);
	if (res == -1)
		return (1);
	return (0);
}

int	connect_pipe(int pipe_fd[2], int stdio)
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
	int i;

	i = 0;
	split_cmd(cmd, argv);
	while (i < 5)
		execve(cmd->file[i++], cmd->argv, cmd->envp);
	perror(cmd->file[0]);
}