/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 15:00:00 by clyon             #+#    #+#             */
/*   Updated: 2025/09/03 15:00:00 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* Handle string format with struct - */
int	handle_string_format_info(va_list args, t_format_info info)
{
	return (handle_string_format(args, info));
}

/* Handle integer format with struct -*/
int	handle_integer_format_info(va_list args, t_format_info info)
{
	return (handle_integer_format(args, info));
}

/* Handle unsigned format with struct - */
int	ft_print_unsigned_formatted_info(va_list args, t_format_info info)
{
	unsigned int	n;

	n = va_arg(args, unsigned int);
	return (ft_print_unsigned_formatted(n, info));
}

/* Handle hex format with struct - */
int	ft_print_hex_formatted_info(va_list args, t_format_info info)
{
	unsigned int	n;

	n = va_arg(args, unsigned int);
	return (ft_print_hex_formatted(n, info));
}

/* Handle pointer format with struct - */
int	ft_print_ptr_formatted_info(va_list args, t_format_info info)
{
	unsigned long long	ptr;

	ptr = va_arg(args, unsigned long long);
	return (ft_print_ptr_formatted(ptr, info.width, info.left_align));
}
