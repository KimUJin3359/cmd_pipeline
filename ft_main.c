#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
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

int	main(int ac, char *av[])
{
	
	int	pipe_fd[2];
	int	res;
	pid_t	pid;

	res = pipe(pipe_fd);
	if (res < 0)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid > 0)
	{
		int	status;
		char	buf[128];

		res = waitpid(pid, &status, 0);
		if (res == -1)
		{
			perror("waitpid");
			exit(1);
		}
		res = redirect_output(av[4]);
		if (res)
		{
			//perror
			exit(1);
		}
		res = connect_pipe(pipe_fd, STDIN_FILENO);
		if (res)
		{
			//perror
			exit(1);
		}
		read(0, buf, sizeof(buf));
		// running cmd2
		// execve
		// pid == 0 과 동일 처리
		// write(1, ~)
		// 후 종료
	}
	else if (pid == 0)
	{
		redirect_input(av[1]);
		connect_pipe(pipe_fd, STDOUT_FILENO);
		// av[2]를 분리 ('' ₩₩)
		// (1 arg)명령어 부분 + (2 arg)인자 부분
		// 명령어 위치 /bin, /sbin, /usr/bin, /usr/sbin, /usr/local/bin
		//execve(av[2]
		exit(0);
	}
	return (0);
}
