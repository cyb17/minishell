/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:02:21 by achevala          #+#    #+#             */
/*   Updated: 2023/11/06 18:51:37 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var_to_exp(char *s);
char	*my_strjoin(char const *s1, char const *s2);


char *expand_value(char *s, int i)
{
	char	*to_expand;
	char	*expanded;
	char 	*tmp;
	int 	j;

	j = 0;
	tmp = s;
	while (j <= i)
	{
		tmp++;
		j++;
	}
	to_expand = get_var_to_exp(tmp);
	expanded = getenv(to_expand);
	free(to_expand);
	if (!expanded)
		return (NULL);
	return (expanded);
}

char    *clean_word(char *s, )
{
    int     len;
    int     i;
    char    *tmp;
    char    *cpy;
	char	*cpy2;

    len = strlen(s);
    i = 0;
	cpy = NULL;
    // if (s[i] == '"' && s[len] == '"')
    // {
	// 	len = len - 1;
	// 	i++;
        while (i <= len)
        {
			if (s[i] != '$')
			{
				if (cpy == NULL)
					cpy = ft_strdup_section(s, i, i + 1);
				else
				{
					tmp = ft_strdup_section(s, i, i + 1);
					cpy2 = cpy;
					cpy = my_strjoin(cpy2, tmp);
					if (cpy2)
						free(cpy2);
					if (tmp != NULL)
						free(tmp);
				}
				i++;
			}
			if (s[i] == '$')
			{
            	tmp = expand_value(s, i);
				if (tmp != NULL);
				{
					cpy2 = cpy;
					cpy = my_strjoin(cpy2, tmp);
					if (cpy2)
						free(cpy2);
					i++;
				}
				while (s[i] >= '0' && s[i] <= '9' || s[i] >= 'A' && s[i] <= 'Z' 
				|| s[i] >= 'a' && s[i] <= 'z' || s[i] == '_')
					i++;
			}
		}
        printf("cpy : %s\n", cpy);
		return (cpy);
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
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int main(int ac, char **av, char **env)
{
	char 		*input;
	//t_process	**process;
    char        *s;
	t_list		*envlist;

	(void)ac;
	(void)av;
	//process_init(&process);
	envlist = env_to_envlist(env);
    input = "coucou  '$US'ER' $PWD hello";
	s = clean_word(input, envlist);
	free(s);
    return (0);
}

