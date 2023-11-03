/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:02:21 by achevala          #+#    #+#             */
/*   Updated: 2023/11/03 17:55:48 by achevala         ###   ########.fr       */
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
//	freetab(var);
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
    // if (s[i] == '"' && s[len] == '"')
    // {
        tmp = ft_strrchr(s, '$');
        if (tmp == NULL)
            return (ft_strdup_section(s, 1, len - 1));
        else
            exp = expand_value(tmp);
        printf("exp : %s\n", exp);
    // }  
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

// int	*ft_strrchr_pos(const char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	while (i >= 0)
// 	{
// 		if (s[i] == (unsigned char)c)
// 			return ((char *)&s[i]);
// 		i--;
// 	}
// 	return (NULL);
// }

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
    input = "coucou  $USER $PWD hello";
	s = clean_word(input);
    return (0);
}
