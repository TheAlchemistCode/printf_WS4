/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 14:30:00 by clyon             #+#    #+#             */
/*   Updated: 2025/09/03 14:30:00 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 
 * t_format_info struct definition (from ft_printf.h):
 * typedef struct s_format_info
 * {
 *     int    width;        // Field width (e.g., %10d)
 *     int    left_align;   // Left alignment flag (- flag)
 *     int    precision;    // Precision (.5 in %.5s, -1 if not set)
 *     int    zero_pad;     // Zero padding flag (0 flag)
 *     char   specifier;    // Format specifier (c, s, d, i, u, x, X, p, %)
 * } t_format_info;
 */

/* Initialize format info structure with default values */
void	init_format_info(t_format_info *info)
{
	info->width = 0;
	info->left_align = 0;
	info->precision = -1;
	info->zero_pad = 0;
	info->specifier = '\0';
}

/* Parse flags from format string */
void	parse_flags_info(const char *str, int *i, t_format_info *info)
{
	while (str[*i] == '-' || str[*i] == '0' || str[*i] == '+' || 
		   str[*i] == ' ' || str[*i] == '#')
	{
		if (str[*i] == '-')
			info->left_align = 1;
		if (str[*i] == '0')
			info->zero_pad = 1;
		(*i)++;
	}
}

/* Parse width from format string */
void	parse_width_info(const char *str, int *i, t_format_info *info)
{
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		info->width = info->width * 10 + (str[*i] - '0');
		(*i)++;
	}
}

/* Parse precision from format string */
void	parse_precision_info(const char *str, int *i, t_format_info *info)
{
	if (str[*i] == '.')
	{
		(*i)++;
		info->precision = 0;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			info->precision = info->precision * 10 + (str[*i] - '0');
			(*i)++;
		}
	}
}

/* Parse format string - REDUCED from 6 parameters to 3! */
char	parse_format_info(const char *str, int *i, t_format_info *info)
{
	init_format_info(info);
	(*i)++;
	parse_flags_info(str, i, info);
	parse_width_info(str, i, info);
	parse_precision_info(str, i, info);
	info->specifier = str[*i];
	return (info->specifier);
}
