/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:51:45 by cblasphe          #+#    #+#             */
/*   Updated: 2020/07/26 16:51:48 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_ifnonflag(t_mods *mods, const char *format, int i)
{
	if (!format[i] || i < 0)
		return (i);
	if (FLAGS & F_FMT_MINUS)
		ft_push_buffer(mods, format[i++]);
	mods->buf_index = ft_normalize_width(mods, 1);
	if (!(FLAGS & F_FMT_MINUS))
		ft_push_buffer(mods, format[i++]);
	return (i);
}

void	ft_flush(t_mods *mods)
{
	FLAGS = 0;
	WIDTH = 0;
	PREC = -1;
	LENGTH = 0;
	SIGN = 0;
}

t_mods	*ft_init(void)
{
	t_mods	*mods;

	mods = ft_memalloc(sizeof(t_mods));
	TOTAL_LEN = 0;
	ft_clear_buffer(mods);
	ft_flush(mods);
	return (mods);
}

int		ft_printf(const char *format, ...)
{
	size_t		i;
	t_mods		*mods;

	i = 0;
	mods = ft_init();
	va_start(ARGS, format);
	ft_parse_format(format, mods, i);
	ft_pop_buffer(mods);
	va_end(ARGS);
	free(mods);
	return (TOTAL_LEN);
}
