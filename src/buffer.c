/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:51:07 by cblasphe          #+#    #+#             */
/*   Updated: 2020/07/26 16:51:14 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_clear_buffer(t_mods *mods)
{
	BUF_INDEX = 0;
	POS = 0;
}

void	ft_pop_buffer(t_mods *mods)
{
	write(1, mods->buf, BUF_INDEX);
	ft_clear_buffer(mods);
}

int		ft_buffer_is_full(t_mods *mods)
{
	return (BUF_INDEX == BUF_SIZE);
}

void	ft_push_buffer(t_mods *mods, char c)
{
	if (ft_buffer_is_full(mods))
		ft_pop_buffer(mods);
	TOTAL_LEN++;
	mods->buf[BUF_INDEX++] = c;
}

void	ft_push_str_to_buffer(t_mods *mods, char *str)
{
	while (*str)
	{
		ft_push_buffer(mods, *str);
		str++;
	}
}
