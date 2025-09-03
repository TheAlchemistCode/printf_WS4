/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:00:00 by clyon             #+#    #+#             */
/*   Updated: 2025/09/03 10:00:00 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Handle string formatting with struct - REFACTORED to use ≤4 parameters!
 * UPDATE_11: Fixed NULL precision logic - precision >= 6 shows "(null)", < 6 shows empty */
int	handle_string_format(va_list args, t_format_info info)
{
	char	*content;
	char	*processed;
	int		result;

	content = va_arg(args, char *);
	if (!content)
	{
		if (info.precision >= 0 && info.precision < 6)
			return (apply_width("", info.width, info.left_align));
		content = "(null)";
	}
	if (info.precision == 0)
		return (apply_width("", info.width, info.left_align));
	if (info.precision >= 0)
	{
		processed = apply_string_precision(content, info.precision);
		result = apply_width(processed, info.width, info.left_align);
		if (processed != content)
			free(processed);
	}
	else
		result = apply_width(content, info.width, info.left_align);
	return (result);
}

/* Handle integer formatting with struct - REFACTORED to use ≤4 parameters! */
int	handle_integer_format(va_list args, t_format_info info)
{
	char	*content;
	char	*processed;
	int		result;
	int		value;

	value = va_arg(args, int);
	if (should_hide_zero(value, info.precision))
		return (apply_width("", info.width, info.left_align));
	content = ft_itoa(value);
	if (info.precision >= 0)
	{
		processed = apply_number_precision(content, info.precision, (value < 0));
		result = apply_width(processed, info.width, info.left_align);
		if (processed != content)
			free(processed);
	}
	else
		result = apply_width_with_zeros(content, info.width, info.left_align, info.zero_pad);
	free(content);
	return (result);
}
