/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 00:00:00 by clyon             #+#    #+#             */
/*   Updated: 2025/09/02 00:00:00 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* NEW: Print n spaces and return the count - helper for width padding */
int	print_spaces(int count)
{
	int	printed;

	printed = 0;
	while (printed < count)
	{
		ft_print_chr(' ');
		printed++;
	}
	return (printed);
}

/* NEW: str width formatting - handles left/right alignment with padding
 * UPDATE_14: Fixed double counting of content length in return value */
int	apply_width(char *content, int width, int left_align)
{
	int	content_len;
	int	padding;
	int	total;

	if (!content)
		return (0);
	content_len = ft_strlen(content);
	if (width <= content_len)
		return (ft_print_str(content));
	padding = width - content_len;
	total = 0;
	if (left_align)
	{
		total += ft_print_str(content);
		total += print_spaces(padding);
	}
	else
	{
		total += print_spaces(padding);
		total += ft_print_str(content);
	}
	return (total);
}

/* NEW: chr width formatting - handles %c with width specifiers
 * UPDATE_12: Fixed double counting of character in return value */
int	apply_char_width(char c, int width, int left_align)
{
	int	padding;
	int	total;

	if (width <= 1)
		return (ft_print_chr(c));
	padding = width - 1;
	total = 0;
	if (left_align)
	{
		total += ft_print_chr(c);
		total += print_spaces(padding);
	}
	else
	{
		total += print_spaces(padding);
		total += ft_print_chr(c);
	}
	return (total);
}

/* Parse format string using t_format_info struct - reduced from 6 to 3 params
 * Captures precision (.3) and zero-padding (0) flags
 * Split flag parsing to helper function for brevity
 * Returns format specifier character
 * Uses struct instead of individual parameters */
char	parse_format(const char *str, int *i, t_format_info *info)
{
	info->width = 0;
	info->left_align = 0;
	info->precision = -1;
	info->zero_pad = 0;
	(*i)++;
	parse_flags(str, i, &info->left_align, &info->zero_pad);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		info->width = info->width * 10 + (str[*i] - '0');
		(*i)++;
	}
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
	info->specifier = str[*i];
	return (str[*i]);
}
