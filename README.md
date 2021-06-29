# my_pipe_cmd

### Project
```
./pipex file1 cmd1 cmd2 file2
```
- this program behavior likes below command.

```
< file1 cmd1 | cmd2 > file2
```

### Using Function

- open
- close
- read
- write
- malloc : memory leaks must not exist
- free
- dup2
```
int dup2(int fd1, int fd2);
// makes fd2 to fd1
// using likes
// dup2(fd, STDIN_FILENO)
// programmer's standard input is changed to fd 
```
- fork : make another process
- pipe 
```
int pipe(int pipefd[2]);
// creates a pipe for communication with another process
// pipefd[0] is using for read
// it's easy to think stdin(0)
// pipefd[1] is using for write
// it's easy to think stdout(1)
```
- execve : change process to another
```
int execve(const char *filename, char *const argv[], char *const envp[]);
// execute program named 'filename' with option 'argv'
// existing program is changed to new program
```
- waitpid : wait until child process dead
- strerror
- exit
