/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treatn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:53:11 by cblasphe          #+#    #+#             */
/*   Updated: 2020/07/26 16:56:07 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_ifn(t_mods *mods)
{
	int	*val;

	val = (int*)va_arg(ARGS, int *);
	*val = TOTAL_LEN;
}
