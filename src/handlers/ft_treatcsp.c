/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treatcsp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:52:27 by cblasphe          #+#    #+#             */
/*   Updated: 2020/07/26 16:52:31 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_normalize_width(t_mods *mods, size_t len)
{
	if ((FLAGS & F_ZERO) && (SIGN < 0 || SIGN == 1 || FLAGS & F_HASH))
	{
		if (SIGN == 1 && FLAGS & F_SPACE)
			ft_push_buffer(mods, ' ');
		else if (SIGN == 1 || SIGN < 0)
			ft_push_buffer(mods, (SIGN < 0) ? '-' : '+');
		else if (FLAGS & F_HASH)
		{
			ft_push_buffer(mods, '0');
			if (TYPE == 'x' || TYPE == 'X')
				ft_push_buffer(mods, TYPE);
			FLAGS &= ~F_HASH;
		}
		SIGN = 2;
		FLAGS &= ~F_SPACE;
	}
	while (WIDTH - (int)len > 0)
	{
		ft_push_buffer(mods, (FLAGS & F_ZERO) ? '0' : ' ');
		WIDTH--;
	}
	return (BUF_INDEX);
}

int		ft_putstrwithprec(t_mods *mods, int precision, char *str, size_t len)
{
	size_t count;
	size_t limit;

	count = 0;
	limit = (precision >= 0) ? (size_t)precision : len;
	while (count < limit)
		ft_push_buffer(mods, str[count++]);
	return (BUF_INDEX);
}

void	ft_ifchar(t_mods *mods)
{
	unsigned char c;

	c = (unsigned char)va_arg(ARGS, int);
	if (FLAGS & F_FMT_MINUS)
		ft_push_buffer(mods, c);
	BUF_INDEX = ft_normalize_width(mods, 1);
	if (!(FLAGS & F_FMT_MINUS))
		ft_push_buffer(mods, c);
}

void	ft_ifstr(t_mods *mods)
{
	char	*str;
	size_t	len;
	size_t	precision;

	FLAGS &= ~F_PLUS;
	FLAGS &= ~F_SPACE;
	if (!(str = (char *)va_arg(ARGS, char *)))
		str = "(null)";
	len = ft_strlen(str);
	if ((size_t)PREC > len)
		PREC = -1;
	if (FLAGS & F_FMT_MINUS)
		BUF_INDEX = ft_putstrwithprec(mods, PREC, str, len);
	precision = (PREC >= 0) ? (size_t)PREC : len;
	BUF_INDEX = ft_normalize_width(mods, precision);
	if (!(FLAGS & F_FMT_MINUS))
		BUF_INDEX = ft_putstrwithprec(mods, PREC, str, len);
}

void	ft_ifptr(t_mods *mods)
{
	uintmax_t	p;
	char		*str_pval;
	size_t		len;

	FLAGS |= F_HASH;
	p = (uintmax_t)va_arg(ARGS, void *);
	str_pval = ft_itoa_base_printf(p, 16, 'a');
	len = ft_strlen(str_pval);
	if (!PREC && !p)
	{
		BUF_INDEX = ft_prec_numb(mods, str_pval, len - 1, 'x');
		return ;
	}
	if (FLAGS & F_FMT_MINUS)
		BUF_INDEX = ft_prec_numb(mods, str_pval, len, 'x');
	BUF_INDEX = ft_normalize_width(mods, len + 2);
	if (WIDTH < PREC)
		WIDTH = PREC;
	if (!(FLAGS & F_FMT_MINUS))
		BUF_INDEX = ft_prec_numb(mods, str_pval, len, 'x');
	if (str_pval)
		ft_strdel(&str_pval);
}
