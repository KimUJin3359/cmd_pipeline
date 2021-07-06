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
	int		i;
	char	*tmp;
	char	**word;

	i = 0;
	word = ft_split(argv, ' ');
	if (!word)
		print_error(2, NULL);
	else if (!word[0])
		print_error(1, "");
	while (cmd->file[i])
	{
		tmp = ft_strjoin(cmd->file[i], "/");
		free(cmd->file[i]);
		cmd->file[i] = tmp;
		tmp = ft_strjoin(cmd->file[i], word[0]);
		free(cmd->file[i]);
		cmd->file[i] = tmp;
		i++;
	}
	cmd->cmd = ft_strdup(word[0]);
	cmd->argv = (char *const *)word;
	cmd->envp = NULL;
}

void	run_cmd(t_cmd *cmd, const char *argv)
{
	int		i;

	i = 0;
	split_cmd(cmd, argv);
	while (cmd->file[i])
		execve(cmd->file[i++], cmd->argv, cmd->envp);
	print_error(1, cmd->cmd);
}
