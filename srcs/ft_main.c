#include "ft_h.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

void	exit_program(const char *msg)
{
	perror(msg);
	exit(1);
}

int	main(int ac, char *av[])
{
	int	pipe_fd[2];
	int	res;
	pid_t	pid;
	t_cmd	cmd;

	if (ac != 5)
		exit(0);
	res = pipe(pipe_fd);
	if (res < 0)
		exit_program("pipe error");
	pid = fork();
	if (pid < 0)
		exit_program("fork error");	
	if (pid > 0)
	{
		int	status;
		char	buf[128];

		res = waitpid(pid, &status, 0);
		if (!WIFEXITED(status))
			exit_program("fork child error");
		if (res == -1)
			exit_program("waitpid error");
		res = redirect_output(av[4]);
		if (res)
			exit_program("redirect output error");
		res = connect_pipe(pipe_fd, STDIN_FILENO);
		if (res)
			exit_program("connect pipe error");
		run_cmd(&cmd, av[3]);
	}
	else if (pid == 0)
	{
		res = redirect_input(av[1]);
		if (res)
			exit_program("redirect input error");
		res = connect_pipe(pipe_fd, STDOUT_FILENO);
		if (res)
			exit_program("connect pipe error");
		run_cmd(&cmd, av[2]);
	}
	return (0);
}
