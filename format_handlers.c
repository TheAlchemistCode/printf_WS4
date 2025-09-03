/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 20:18:28 by clyon             #+#    #+#             */
/*   Updated: 2025/09/03 20:18:28 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Handle string format with struct - */
int	handle_string_format_spec(va_list args, t_format_spec spec)
{
	return (handle_string_format(args, spec));
}

/* Handle integer format with struct -*/
int	handle_integer_format_spec(va_list args, t_format_spec spec)
{
	return (handle_integer_format(args, spec));
}

/* Handle unsigned format with struct - */
int	ft_print_unsigned_formatted_spec(va_list args, t_format_spec spec)
{
	unsigned int	n;

	n = va_arg(args, unsigned int);
	return (ft_print_unsigned_formatted(n, spec));
}

/* Handle hex format with struct - */
int	ft_print_hex_formatted_spec(va_list args, t_format_spec spec)
{
	unsigned int	n;

	n = va_arg(args, unsigned int);
	return (ft_print_hex_formatted(n, spec));
}

/* Handle pointer format with struct - */
int	ft_print_ptr_formatted_spec(va_list args, t_format_spec spec)
{
	unsigned long long	ptr;

	ptr = va_arg(args, unsigned long long);
	return (ft_print_ptr_formatted(ptr, spec.width, spec.left_align));
}
