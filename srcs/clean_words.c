/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:02:21 by achevala          #+#    #+#             */
/*   Updated: 2023/11/05 21:01:01 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var_to_exp(char *s);

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
	//tmp++;
	to_expand = get_var_to_exp(tmp);
	expanded = getenv(to_expand);
	free(to_expand);
	return (expanded);
}

char    *clean_word(char *s)
{
    int     len;
    int     i;
    char    *tmp;
    char    *cpy;

    len = strlen(s);
    i = 0;
	cpy = NULL;
    // if (s[i] == '"' && s[len] == '"')
    // {
	// 	len = len - 1;
	// 	i++;
        while (i <= len)
        {
			// if (tmp)
			// 	free(tmp);
			if (s[i] != '$')
			{
				if (cpy == NULL)
					cpy = ft_strdup_section(s, i, i + 1);
				else
				{
					tmp = ft_strdup_section(s, i, i + 1);
					cpy = ft_strjoin(cpy, tmp);
//					free(tmp);
				}
				i++;
			}
			if (s[i] == '$')
			{
            	tmp = expand_value(s, i);
				cpy = ft_strjoin(cpy, tmp);
				i++;
//				free(tmp);
				while (s[i] >= '0' && s[i] <= '9' || s[i] >= 'A' && s[i] <= 'Z' 
				|| s[i] >= 'a' && s[i] <= 'z' || s[i] == '_')
					i++;
			}
		}
        printf("cpy : %s\n", cpy);
    }  
//}

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
	while (s[i] != '\0')
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
