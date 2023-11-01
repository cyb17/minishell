/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:41:06 by achevala          #+#    #+#             */
/*   Updated: 2023/11/01 12:47:19 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char **environ;

char **get_environment() 
{
    int i;
    int j;
    char **env_copy = NULL;

    i = 0;
    j = 0;
    while (environ[i] != NULL)
        i++;
    env_copy = (char **)malloc((i + 1) * sizeof(char *));
    if (env_copy == NULL) 
    {
        perror("Erreur d'allocation de mémoire");
        exit(1);
    }
    while (j < i) 
    {
        env_copy[j] = ft_strdup(environ[j]);
        j++;
    }
    env_copy[i] = NULL; 
    return env_copy;
}

int main() {
    char **environment = get_environment();
    if (environment != NULL) {
        int i = 0;
        while (environment[i] != NULL) {
            printf("%s\n", environment[i]);
            free(environment[i]);
            i++;
        }
        free(environment);
    }

    return 0;
}
