/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:06:10 by achevala          #+#    #+#             */
/*   Updated: 2023/11/27 12:31:19 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

/* void    clear_process(t_process *process)
{
    t_tokens    *tokenslist;
    t_tokens    *tmp;

    tokenslist = process->list_tokens;
    tmp = NULL;
    free_tab(&process->section_cmd);
    while (tokenslist != NULL)
    {
        tmp = (tokenslist)->next;
        if ((tokenslist)->value != NULL)
            free((tokenslist)->value);
        free(tokenslist);
        tokenslist = tmp;
    }
} */
/* 
void    garbage_collector(t_process *process_list)
{
    t_process    *tmp;

    tmp = NULL;
    while (process_list != NULL)
    {
        tmp = (process_list)->next;
        clear_process(process_list);
        process_list = tmp;
    }
} */