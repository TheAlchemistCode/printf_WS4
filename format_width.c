/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 20:17:55 by clyon             #+#    #+#             */
/*   Updated: 2025/09/03 20:17:55 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Handle string formatting with struct - REFACTORED to use ≤4 parameters!
 * UPDATE_11: Fixed NULL precision logic - 
 * precision >= 6 shows "(null)", < 6 shows empty */
int	handle_string_format(va_list args, t_format_spec spec)
{
	char	*content;
	char	*processed;
	int		result;

	content = va_arg(args, char *);
	if (!content)
	{
		if (spec.precision >= 0 && spec.precision < 6)
			return (apply_width("", spec.width, spec.left_align));
		content = "(null)";
	}
	if (spec.precision == 0)
		return (apply_width("", spec.width, spec.left_align));
	if (spec.precision >= 0)
	{
		processed = apply_string_precision(content, spec.precision);
		result = apply_width(processed, spec.width, spec.left_align);
		if (processed != content)
			free(processed);
	}
	else
		result = apply_width(content, spec.width, spec.left_align);
	return (result);
}

/* Handle integer formatting with struct - REFACTORED to use ≤4 parameters! */
int	handle_integer_format(va_list args, t_format_spec spec)
{
	char	*content;
	char	*processed;
	int		result;
	int		value;

	value = va_arg(args, int);
	if (should_hide_zero(value, spec.precision))
		return (apply_width("", spec.width, spec.left_align));
	content = ft_itoa(value);
	if (spec.precision >= 0)
	{
		processed = apply_no_prec(content, spec.precision, (value < 0));
		result = apply_width(processed, spec.width, spec.left_align);
		if (processed != content)
			free(processed);
	}
	else
		result = zero_space_padr(content, spec.width,
				spec.left_align, spec.zero_pad);
	free(content);
	return (result);
}
