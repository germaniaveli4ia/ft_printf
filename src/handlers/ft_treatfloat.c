/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treatfloat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:52:43 by cblasphe          #+#    #+#             */
/*   Updated: 2020/07/26 16:55:58 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_float2(t_mods *mods, long double val, char *str, int fract_len)
{
	size_t	ful_len;
	size_t	i;

	i = 0;
	ful_len = ft_strlen(str);
	if (TYPE == 'F')
		while (i < ful_len)
			ft_toupper(str[i++]);
	if (PREC < fract_len && val != 0)
		PREC = -1;
	if ((SIGN != 0 || FLAGS & F_SPACE) && WIDTH)
		WIDTH -= 1;
	if (val != val)
	{
		FLAGS &= ~F_ZERO & ~F_SPACE;
		SIGN = 0;
	}
	if (FLAGS & F_FMT_MINUS)
		BUF_INDEX = ft_prec_float(mods, str);
	BUF_INDEX = ft_normalize_width(mods, ful_len);
	SIGN = (SIGN == 2) ? 0 : SIGN;
	if (!(FLAGS & F_FMT_MINUS))
		BUF_INDEX = ft_prec_float(mods, str);
	if (str)
		ft_strdel(&str);
}

int16_t		*ft_get_fract_digs(t_mods *mods, long double val)
{
	short int		*digs;
	int				i;

	if (!(digs = (short int*)ft_memalloc((PREC + 1) * sizeof(short int))))
		return (NULL);
	i = 0;
	val -= (uintmax_t)val;
	while (i <= PREC)
	{
		val *= 10;
		digs[i] = (int)val;
		val -= (int)val;
		i++;
	}
	return (digs);
}

int			ft_getdec_len(uintmax_t tmp, long double val)
{
	int				dec_len;

	dec_len = 0;
	while (tmp)
	{
		tmp = tmp / 10;
		dec_len++;
	}
	dec_len = ((long long)val == 0) ? 1 : dec_len;
	return (dec_len);
}

void		ft_treatfloat1(t_mods *mods, long double val)
{
	char			*str_val;
	int				i;

	str_val = NULL;
	i = 0;
	if (val == FT_INF)
	{
		FLAGS &= ~F_ZERO;
		str_val = ft_strdup("inf");
	}
	else if (val != val)
		str_val = ft_strdup("nan");
	else
		str_val = ft_getstr_val(mods, val, str_val, i);
	ft_float2(mods, val, str_val, PREC);
}

void		ft_iffloat(t_mods *mods)
{
	long double	val;

	val = 0.0;
	if (LENGTH == LD)
		val = va_arg(ARGS, long double);
	else
		val = (long double)va_arg(ARGS, double);
	if (PREC < 0)
		PREC = 6;
	if (val < 0)
	{
		SIGN = -1;
		val *= -1;
		FLAGS &= ~F_SPACE;
	}
	else if (val >= 0 && (FLAGS & F_PLUS || FLAGS & F_SPACE))
		SIGN = 1;
	ft_treatfloat1(mods, val);
}
