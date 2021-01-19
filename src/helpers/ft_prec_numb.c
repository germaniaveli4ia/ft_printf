/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prec_numb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:53:54 by cblasphe          #+#    #+#             */
/*   Updated: 2020/07/26 16:54:46 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_get_limit(t_mods *mods, size_t len)
{
	if (TYPE == 'f')
		return (len);
	return ((PREC > 0) ? (size_t)PREC : len);
}

void	ft_push_sign(t_mods *mods)
{
	if (SIGN == 1 && FLAGS & F_PLUS)
		ft_push_buffer(mods, '+');
	else if (SIGN < 0)
		ft_push_buffer(mods, '-');
	else if (FLAGS & F_SPACE)
		ft_push_buffer(mods, ' ');
}

int		ft_prec_numb(t_mods *mods, char *str, size_t len, char utype)
{
	int		count;
	size_t	limit;

	count = 0;
	limit = ft_get_limit(mods, len);
	ft_push_sign(mods);
	if ((FLAGS & F_HASH) && utype)
		ft_push_buffer(mods, '0');
	if ((FLAGS & F_HASH) && (utype == 'x' || utype == 'X'))
		ft_push_buffer(mods, utype);
	if (PREC > 0 && ft_strchr("dipuoxX", TYPE))
		while (len++ < limit)
			ft_push_buffer(mods, '0');
	if (TYPE == 'p')
		limit = len;
	while (PREC && str[count] && (size_t)count < limit)
		ft_push_buffer(mods, str[count++]);
	return (BUF_INDEX);
}

int		ft_prec_float(t_mods *mods, char *str)
{
	ft_push_sign(mods);
	ft_push_str_to_buffer(mods, str);
	return (BUF_INDEX);
}
