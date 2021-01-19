/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treatuox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:53:24 by cblasphe          #+#    #+#             */
/*   Updated: 2020/07/26 16:55:13 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*ft_itoa_base_printf(uintmax_t n, int base, char type)
{
	char		*str;
	int			len;
	uintmax_t	tmp;

	len = 0;
	tmp = n;
	if (tmp == 0)
		return (ft_strdup("0"));
	while (tmp)
	{
		tmp /= base;
		++len;
	}
	str = ft_strnew(len);
	if (str == NULL)
		return (NULL);
	while (len)
	{
		str[--len] = (n % base < 10) ? n % base + '0' : n % base - 10 + type;
		n /= base;
	}
	return (str);
}

void		ft_treatuox(t_mods *mods, uintmax_t val, int base, char type)
{
	char	*str_val;
	size_t	len;

	str_val = NULL;
	FLAGS &= ~F_SPACE;
	if (FLAGS & F_HASH)
	{
		WIDTH -= (base == 16) ? 2 : 1;
		PREC -= (type == 'o') ? 1 : 0;
	}
	str_val = ft_itoa_base_printf(val, base, ft_isupper(type) ? 'A' : 'a');
	len = ft_strlen(str_val);
	if ((size_t)PREC < len && val != 0)
		PREC = -1;
	if (FLAGS & F_FMT_MINUS)
		BUF_INDEX = ft_prec_numb(mods, str_val, len, type);
	BUF_INDEX = ft_normalize_width(mods,
						(PREC >= 0 ? (size_t)PREC : len));
	if (!(FLAGS & F_FMT_MINUS))
		BUF_INDEX = ft_prec_numb(mods, str_val, len, type);
	free(str_val);
}

uintmax_t	ft_getuval(char type, int length, t_mods *mods)
{
	uintmax_t	val;

	val = 0;
	if (type == 'U')
		val = (unsigned long)va_arg(ARGS, unsigned long);
	else if (!length)
		val = (unsigned int)va_arg(ARGS, unsigned int);
	else if (length == 2 * H)
		val = (unsigned char)va_arg(ARGS, int);
	else if (length == H)
		val = (unsigned short int)va_arg(ARGS, int);
	else if (length == L)
		val = (unsigned long int)va_arg(ARGS, unsigned long int);
	else if (length == 2 * L)
		val = (uintmax_t)va_arg(ARGS, unsigned long long int);
	else if (length == J)
		val = (uintmax_t)va_arg(ARGS, uintmax_t);
	else if (length == Z)
		val = (size_t)va_arg(ARGS, size_t);
	else
		val = (unsigned long)va_arg(ARGS, unsigned long);
	return (val);
}

void		ft_ifunsigned(t_mods *mods, char type)
{
	uintmax_t	val;
	int			base;

	val = 0;
	val = ft_getuval(TYPE, LENGTH, mods);
	if (type == 'o')
		base = 8;
	else if (type == 'u' || type == 'U')
		base = 10;
	else
		base = 16;
	if (!val && PREC < 0 && FLAGS & F_DOT)
		PREC = 0;
	if ((val && PREC < 0 && FLAGS & F_DOT)
			|| (!val && !PREC && (FLAGS & F_HASH) && base == 8))
		PREC = 1;
	if (!val || base == 10)
		FLAGS &= ~F_HASH;
	FLAGS = (PREC >= 0) ? FLAGS & ~F_ZERO : FLAGS;
	ft_treatuox(mods, val, base, type);
}
