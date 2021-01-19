/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifications.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cblasphe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 16:52:04 by cblasphe          #+#    #+#             */
/*   Updated: 2020/07/26 16:55:38 by cblasphe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_flags(char cur_char, t_mods *mods)
{
	if (cur_char == '-')
		FLAGS |= F_FMT_MINUS;
	else if (cur_char == '+')
		FLAGS |= F_PLUS;
	else if (cur_char == ' ')
		FLAGS |= F_SPACE;
	else if (cur_char == '#')
		FLAGS |= F_HASH;
	else if (cur_char == '0' && !(FLAGS & F_DOT) && !WIDTH)
		FLAGS |= F_ZERO;
	else
		return (0);
	if (FLAGS & F_FMT_MINUS)
		FLAGS &= ~F_ZERO;
	if (FLAGS & F_PLUS)
		FLAGS &= ~F_SPACE;
	return (1);
}

int		ft_width(char cur_char, t_mods *mods)
{
	if (FLAGS & F_DOT)
		return (0);
	if (cur_char != '*' && !ft_isdigit(cur_char))
		return (0);
	if (cur_char == '*')
	{
		FLAGS |= F_STAR;
		WIDTH = va_arg(ARGS, int);
		if (WIDTH < 0)
		{
			WIDTH *= -1;
			FLAGS |= F_FMT_MINUS;
			FLAGS &= ~F_ZERO;
		}
	}
	if (ft_isdigit(cur_char))
	{
		if (FLAGS & F_STAR)
			WIDTH = 0;
		FLAGS &= ~F_STAR;
		WIDTH = WIDTH * 10 + (cur_char - '0');
	}
	return (1);
}

int		ft_precision(char cur_char, t_mods *mods)
{
	if (cur_char == '.')
	{
		FLAGS = (FLAGS & ~F_STAR) | F_DOT;
		PREC = -1;
	}
	else if (cur_char == '*')
	{
		FLAGS |= F_STAR;
		PREC = va_arg(ARGS, int);
		if (PREC <= -1)
		{
			PREC = -1;
			FLAGS &= ~F_DOT;
		}
	}
	else if (ft_isdigit(cur_char)
			&& (FLAGS & F_DOT) && !(FLAGS & F_STAR))
	{
		if (PREC < 0)
			PREC = 0;
		PREC = PREC * 10 + (cur_char - '0');
	}
	else
		return (0);
	return (1);
}
