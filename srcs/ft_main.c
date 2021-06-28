#include "ft_h.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <stdio.h>
#include <string.h>

int		main(int ac, char *av[])
{
	t_cmd	cmd;
	int		pipe_fd[2];
	int		status;
	pid_t	pid;

	if (ac != 5)
		print_error(2, NULL);
	if (pipe(pipe_fd) < 0 || (pid = fork()) < 0)
		exit(1);
	if (pid > 0)
	{
		if (waitpid(pid, &status, 0) == -1)
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

char	*to_lower(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
	}
	return (str);
}

void	print_error(int err, const char *name)
{
	char	*err_msg;

	if (err == 0)
	{
		write(2, "zsh: ", 5);
		if (!(err_msg = ft_strdup(strerror(errno))))
			exit(1);
		err_msg = to_lower(err_msg);
		write(2, err_msg, ft_strlen(err_msg));
		write(2, ": ", 2);
		write(2, name, ft_strlen(name));
	}
	else if (err == 1)
	{
		write(2, "zsh: command not found: ", 24);
		write(2, name, ft_strlen(name));
	}
	else if (err == 2)
		write(2, "zsh: permission denied:", 23);
	else
		write(2, "usage: ./pipex file1 cmd1 cmd2 file2", 36);
	write(2, "\n", 1);
	exit(1);
}
