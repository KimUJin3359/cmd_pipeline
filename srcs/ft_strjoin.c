#include "ft_h.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	int		i;
	int		j;

	if (!(dst = (char *)malloc(sizeof(char) *
		(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dst[i + j] = s2[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*res;

	i = -1;
	if (!(res = (char *)malloc(sizeof(char) + 1)))
		return (NULL);
	while (str[++i])
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}

void	initialize_path(t_cmd *cmd, char *en[])
{
	int i;

	i = 0;
	while (en[i])
	{
		if (ft_strlen(en[i]) >= 5 && en[i][0] == 'P' && en[i][1] == 'A'
				&& en[i][2] == 'T' && en[i][3] == 'H' && en[i][4] == '=')
			cmd->file = ft_split((en[i] + 5), ':');
		i++;
	}
}
