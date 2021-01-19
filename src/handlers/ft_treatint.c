/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treatint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:52:54 by cblasphe          #+#    #+#             */
/*   Updated: 2020/07/26 16:52:57 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_treatint(t_mods *mods, uintmax_t val)
{
	char	*str_val;
	size_t	len;

	str_val = ft_itoa_base_printf(val, 10, 'A');
	len = ft_strlen(str_val);
	if ((size_t)PREC < len && val != 0)
		PREC = -1;
	if ((SIGN != 0 || FLAGS & F_SPACE) && WIDTH)
		WIDTH -= 1;
	if (FLAGS & F_FMT_MINUS)
		BUF_INDEX = ft_prec_numb(mods, str_val, len, SIGN);
	BUF_INDEX = ft_normalize_width(mods,
						(PREC >= 0 ? (size_t)PREC : len));
	SIGN = (SIGN == 2) ? 0 : SIGN;
	if (!(FLAGS & F_FMT_MINUS))
		BUF_INDEX = ft_prec_numb(mods, str_val, len, SIGN);
	if (str_val)
		ft_strdel(&str_val);
}

void	ft_check_sign(t_mods *mods, long long *val)
{
	if (*val < 0)
	{
		SIGN = -1;
		FLAGS &= ~F_SPACE;
		*val *= -1;
	}
	else if (*val >= 0 && (FLAGS & F_PLUS || FLAGS & F_SPACE))
		SIGN = 1;
}

void	ft_ifint(t_mods *mods)
{
	long long int	val;

	val = 0;
	FLAGS &= ~F_HASH;
	if (!LENGTH)
		val = (int)va_arg(ARGS, int);
	else if (LENGTH == 2 * H)
		val = (signed char)va_arg(ARGS, int);
	else if (LENGTH == H)
		val = (short int)va_arg(ARGS, int);
	else if (LENGTH == L)
		val = (long int)va_arg(ARGS, long int);
	else if (LENGTH == 2 * L)
		val = (long long int)va_arg(ARGS, long long int);
	else if (LENGTH == J)
		val = (intmax_t)va_arg(ARGS, intmax_t);
	else if (LENGTH == Z)
		val = (ssize_t)va_arg(ARGS, ssize_t);
	else
		val = (unsigned long)va_arg(ARGS, unsigned long);
	FLAGS = (PREC >= 0) ? FLAGS & ~F_ZERO : FLAGS;
	ft_check_sign(mods, &val);
	ft_treatint(mods, (uintmax_t)val);
}
