/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_part3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:32:13 by yachen            #+#    #+#             */
/*   Updated: 2023/12/02 13:57:17 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

void	free_newvar(t_var *export, t_var *env)
{
	if(export->newvar)
		free(export->newvar);
	if (env->newvar)
		free(env->newvar);
}
