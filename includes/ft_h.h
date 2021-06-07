#ifndef FT_H_H
# define FT_H_H

# include <stdlib.h>

typedef	struct		s_cmd
{
	char		*file[5];
	char *const	*argv;
	char *const	*envp;
}			t_cmd;


size_t		ft_strlen(const char *str);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);

int		redirect_input(const char *file);
int		redirect_output(const char *file);
int		connect_pipe(int pipe_fd[2], int stdio);
void		split_cmd(t_cmd *cmd, const char *argv);
void		run_cmd(t_cmd *cmd, const char *argv);

#endif
