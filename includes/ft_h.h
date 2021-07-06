#ifndef FT_H_H
# define FT_H_H

# include <stdlib.h>

typedef	struct		s_cmd
{
	char			*cmd;
	char			**file;
	char *const		*argv;
	char *const		*envp;
}					t_cmd;

char				**ft_split(char const *s, char c);

size_t				ft_strlen(const char *str);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strdup(char *str);
void				initialize_path(t_cmd *cmd, char *en[]);

int					redirect_input(const char *file);
int					redirect_output(const char *file);
int					connect_pipe(int pipe_fd[2], int stdio);
void				split_cmd(t_cmd *cmd, const char *argv);
void				run_cmd(t_cmd *cmd, const char *argv);

void				print_error(int err, const char *name);

#endif
