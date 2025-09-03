/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 20:18:19 by clyon             #+#    #+#             */
/*   Updated: 2025/09/03 20:18:19 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 
 * t_format_spec struct definition (from ft_printf.h):
 * typedef struct s_format_spec
 * {
 *     int    width;        // Field width (e.g., %10d)
 *     int    left_align;   // Left alignment flag (- flag)
 *     int    precision;    // Precision (.5 in %.5s, -1 if not set)
 *     int    zero_pad;     // Zero padding flag (0 flag)
 *     char   specifier;    // Format specifier (c, s, d, i, u, x, X, p, %)
 * } t_format_spec;
 */

/* Initialize format spec structure with default values */
void	init_format_spec(t_format_spec *spec)
{
	spec->width = 0;
	spec->left_align = 0;
	spec->precision = -1;
	spec->zero_pad = 0;
	spec->specifier = '\0';
}

/* Parse flags from format string */
void	parse_flags_spec(const char *str, int *i, t_format_spec *spec)
{
	while (str[*i] == '-' || str[*i] == '0' || str[*i] == '+'
		|| str[*i] == ' ' || str[*i] == '#')
	{
		if (str[*i] == '-')
			spec->left_align = 1;
		if (str[*i] == '0')
			spec->zero_pad = 1;
		(*i)++;
	}
}

/* Parse width from format string */
void	parse_width_spec(const char *str, int *i, t_format_spec *spec)
{
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		spec->width = spec->width * 10 + (str[*i] - '0');
		(*i)++;
	}
}

/* Parse precision from format string */
void	parse_precision_spec(const char *str, int *i, t_format_spec *spec)
{
	if (str[*i] == '.')
	{
		(*i)++;
		spec->precision = 0;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			spec->precision = spec->precision * 10 + (str[*i] - '0');
			(*i)++;
		}
	}
}

/* Parse format string - REDUCED from 6 parameters to 3! */
char	parse_format_spec(const char *str, int *i, t_format_spec *spec)
{
	init_format_spec(spec);
	(*i)++;
	parse_flags_spec(str, i, spec);
	parse_width_spec(str, i, spec);
	parse_precision_spec(str, i, spec);
	spec->specifier = str[*i];
	return (spec->specifier);
}
