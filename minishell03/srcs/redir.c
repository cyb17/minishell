/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achevala <achevala@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:46:46 by achevala          #+#    #+#             */
/*   Updated: 2023/12/08 15:18:41 by achevala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

bool	three_redir(char *s, t_all *all)
{
	if (my_strnstr(s, "<<<", 3) == true)
		return (ft_error(ERROR_NEWLINE, all, 2));
	if (my_strnstr(s, "<<>", 3) == true)
		return (ft_error(ERROR_REDIR3, all, 2));
	if (my_strnstr(s, "<><", 3) == true)
		return (ft_error(ERROR_REDIR4, all, 2));
	if (my_strnstr(s, "<>>", 3) == true)
		return (ft_error(ERROR_REDIR3, all, 2));
	if (my_strnstr(s, "><<", 3) == true)
		return (ft_error(ERROR_REDIR2, all, 2));
	if (my_strnstr(s, "><>", 3) == true)
		return (ft_error(ERROR_REDIR5, all, 2));
	if (my_strnstr(s, ">><", 3) == true)
		return (ft_error(ERROR_REDIR4, all, 2));
	if (my_strnstr(s, ">>>", 3) == true)
		return (ft_error(ERROR_REDIR3, all, 2));
	return (ft_error(ERROR_REDIR3, all, 2));
}

bool	four_redir(char *s, t_all *all)
{
	if (my_strnstr(s, "<<<<", 4) == true)
		return (ft_error(ERROR_REDIR4, all, 2));
	if (my_strnstr(s, "<<<>", 4) == true)
		return (ft_error(ERROR_REDIR3, all, 2));
	if (my_strnstr(s, "<<><", 4) == true)
		return (ft_error(ERROR_REDIR3, all, 2));
	if (my_strnstr(s, "<<>>", 4) == true)
		return (ft_error(ERROR_REDIR1, all, 2));
	if (my_strnstr(s, "<><<", 4) == true)
		return (ft_error(ERROR_REDIR2, all, 2));
	if (my_strnstr(s, "<><>", 4) == true)
		return (ft_error(ERROR_REDIR5, all, 2));
	if (my_strnstr(s, "<>><", 4) == true)
		return (ft_error(ERROR_REDIR3, all, 2));
	return (four_redir_end(s, all));
}

bool	four_redir_end(char *s, t_all *all)
{
	if (my_strnstr(s, "<>>>", 4) == true)
		return (ft_error(ERROR_REDIR1, all, 2));
	if (my_strnstr(s, "><<<", 4) == true)
		return (ft_error(ERROR_HSTRING, all, 2));
	if (my_strnstr(s, "><<>", 4) == true)
		return (ft_error(ERROR_REDIR2, all, 2));
	if (my_strnstr(s, "><><", 4) == true)
		return (ft_error(ERROR_REDIR5, all, 2));
	if (my_strnstr(s, "><>>", 4) == true)
		return (ft_error(ERROR_REDIR5, all, 2));
	if (my_strnstr(s, ">><<", 4) == true)
		return (ft_error(ERROR_REDIR2, all, 2));
	if (my_strnstr(s, ">><>", 4) == true)
		return (ft_error(ERROR_REDIR5, all, 2));
	if (my_strnstr(s, ">>><", 4) == true)
		return (ft_error(ERROR_REDIR3, all, 2));
	if (my_strnstr(s, ">>>>", 4) == true)
		return (ft_error(ERROR_REDIR1, all, 2));
	return (ft_error(ERROR_REDIR3, all, 2));
}

bool	more_redir(char *s, t_all *all)
{
	if (my_strnstr(s, "<><>", (int)ft_strlen(s)) == true)
		return (ft_error(ERROR_REDIR5, all, 2));
	if (my_strnstr(s, "<<<<<<", (int)ft_strlen(s)) == true)
		return (ft_error(ERROR_HSTRING, all, 2));
	if (my_strnstr(s, "<<<<<", 5) == true)
		return (ft_error(ERROR_REDIR2, all, 2));
	if (my_strnstr(s, "<<<", (int)ft_strlen(s)) == true)
		return (ft_error(ERROR_HSTRING, all, 2));
	if (my_strnstr(s, ">>>>>", (int)ft_strlen(s)) == true)
		return (ft_error(ERROR_REDIR1, all, 2));
	if (my_strnstr(s, ">>", (int)ft_strlen(s)) == true)
		return (ft_error(ERROR_REDIR1, all, 2));
	if (my_strnstr(s, "<<", (int)ft_strlen(s)) == true)
		return (ft_error(ERROR_REDIR2, all, 2));
	return (ft_error(ERROR_MSG, all, 2));
}

bool	pick_redir_error(char *s, t_all *all, int i)
{
	int	j;

	j = i;
	while (s[j] == '<' || s[j] == '>')
		j++;
	if (j - i == 3)
		return (three_redir(s + i, all));
	if (j - i == 4)
		return (four_redir(s + i, all));
	return (more_redir(s + i, all));
}
