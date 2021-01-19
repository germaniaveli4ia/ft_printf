/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:51:29 by cblasphe          #+#    #+#             */
/*   Updated: 2020/07/26 16:51:33 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_parse_modifier(const char *format, t_mods *mods)
{
	if (!ft_strchr("hlLjz", *format))
		return (0);
	if (*format == 'l')
		LENGTH += L;
	else if (*format == 'h')
		LENGTH += H;
	else if (*format == 'L')
		LENGTH += LD;
	else if (*format == 'j')
		LENGTH += J;
	else if (*format == 'z')
		LENGTH += Z;
	return (1);
}

int		ft_parse_spec(const char *format, t_mods *mods, size_t i)
{
	int	modifier;

	modifier = 0;
	if (ft_flags(format[i], mods)
			|| ft_width(format[i], mods)
			|| ft_precision(format[i], mods))
		i++;
	else if ((modifier = ft_parse_modifier(&(format[i]), mods)) > 0)
		i += modifier;
	else
		i++;
	return (i);
}

size_t	ft_parse_type(const char *format, t_mods *mods, size_t i)
{
	POS = i;
	TYPE = format[i];
	if (PREC == -1 && FLAGS & F_DOT)
	{
		PREC = (ft_strchr("cspdi", format[i])) ? 0 : PREC;
		PREC = (format[i] == 'f') ? 6 : PREC;
	}
	if (format[i] == 'c')
		ft_ifchar(mods);
	else if (format[i] == 's')
		ft_ifstr(mods);
	else if (format[i] == 'p')
		ft_ifptr(mods);
	else if (format[i] == 'd' || format[i] == 'i')
		ft_ifint(mods);
	else if (ft_strchr("xXouU", format[i]))
		ft_ifunsigned(mods, format[i]);
	else if (format[i] == 'f' || format[i] == 'F')
		ft_iffloat(mods);
	else if (format[i] == 'n')
		ft_ifn(mods);
	return (i + 1);
}

int		ft_parse_format(const char *format, t_mods *mods, size_t i)
{
	while (format[i] != '\0')
	{
		if (format[i] != '%' || format[i + 1] == '%')
		{
			ft_push_buffer(mods, format[i]);
			format[i] == '%' ? i += 2 : i++;
			continue;
		}
		i++;
		while (format[i] && (ft_strchr(SPECS, format[i])))
			i = ft_parse_spec(format, mods, i);
		if (format[i] && ft_strchr(TYPES, format[i]))
			i = ft_parse_type(format, mods, i);
		else if (!ft_strchr(ALLSIMBOLS, format[i]))
			i = ft_ifnonflag(mods, format, i);
		ft_flush(mods);
	}
	return (BUF_INDEX);
}
