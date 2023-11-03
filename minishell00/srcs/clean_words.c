/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:02:21 by achevala          #+#    #+#             */
/*   Updated: 2023/11/03 17:27:42 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *expand_value(char *tmp)
{
	char	**var;
	char	*expanded;

	tmp++;
	var = ft_split(tmp, ' ');
	expanded = getenv(var[0]);
	freetab(var);
	return (expanded);
}

char    *clean_word(char *s)
{
    int     len;
    int     i;
    char    *tmp;
    char    *exp; 

    len = strlen(s);
    i = 0;
    if (s[i] == '"' && s[len] == '"')
    {
        tmp = ft_strrchr(s, '$');
        if (tmp == NULL)
            return (ft_strdup_section(s, 1, len - 1));
        else
            exp = expand_value(tmp);
        printf("exp : %s\n", exp);
    }  
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] && i < (int)(ft_strlen(s1) + ft_strlen(s2)))
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}	

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int main(int ac, char **av, char **env)
{
	char 		*input;
	//t_process	**process;
    char        *s;
	(void)ac;
	(void)av;
	(void)env;
	//process_init(&process);
    input = "coucou  $USER hello";
	s = clean_word(input);
    return (0);
}