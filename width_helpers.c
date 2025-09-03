/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:00:00 by clyon             #+#    #+#             */
/*   Updated: 2025/09/03 10:00:00 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* NEW: Print n zeros and return the count - helper for zero padding */
int	print_zeros(int count)
{
	int	printed;

	printed = 0;
	while (printed < count)
	{
		ft_print_chr('0');
		printed++;
	}
	return (printed);
}

/* NEW: Handle special zero cases for precision
 * Returns 1 if zero should be hidden (precision 0), 0 otherwise */
int	should_hide_zero(int value, int precision)
{
	return (value == 0 && precision == 0);
}

/* NEW: Helper to print content with left alignment and padding */
int	print_left_aligned(char *content, int padding)
{
	int	total;

	total = ft_print_str(content);
	total += print_spaces(padding);
	return (total);
}

/* NEW: Apply width with zero padding option - handles %05d style formatting
 * UPDATE: Split into smaller functions to meet norminette 25-line limit
 * UPDATE_2: Fixed zero-padding for negative numbers (sign first, then zeros) */
int	apply_width_with_zeros(char *content, int width, int left_align, int zero_pad)
{
	int	content_len;
	int	padding;

	if (!content)
		return (0);
	content_len = ft_strlen(content);
	if (width <= content_len)
		return (ft_print_str(content));
	padding = width - content_len;
	if (left_align)
		return (print_left_aligned(content, padding));
	if (zero_pad && content[0] == '-')
		return (handle_negative_zero_pad(content, padding));
	if (zero_pad)
		return (print_zeros(padding) + ft_print_str(content));
	return (print_spaces(padding) + ft_print_str(content));
}
