/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:38:14 by clyon             #+#    #+#             */
/*   Updated: 2025/09/01 14:38:18 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_len_ptr(uintptr_t num)
{
	size_t	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	ft_put_ptr(uintptr_t ptr)
{
	if (ptr >= 16)
	{
		ft_put_ptr(ptr / 16);
		ft_put_ptr(ptr % 16);
	}
	else
	{
		if (ptr <= 9)
			ft_putchar_fd((ptr + 48), 1);
		else
			ft_putchar_fd((ptr - 10 + 'a'), 1);
	}
}

/* UPDATE: Helper to convert pointer to string for formatting
 * Used by ft_print_ptr_formatted for string manipulation */
void	ft_put_ptr_to_string(uintptr_t ptr, char *str)
{
	int	len;
	int	temp;

	len = ft_len_ptr(ptr);
	str[len] = '\0';
	while (len > 0)
	{
		temp = ptr % 16;
		len--;
		if (temp <= 9)
			str[len] = temp + '0';
		else
			str[len] = temp - 10 + 'a';
		ptr /= 16;
	}
}

int	ft_print_ptr(unsigned long long ptr)
{
	int	length;

	if (ptr == 0)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	length = 2;
	ft_put_ptr(ptr);
	length += ft_len_ptr(ptr);
	return (length);
}

/* UPDATE: Enhanced version with width 
 * and alignment support for pointer formatting
 * Handles format specifiers like %15p, %-20p */
int	ft_print_ptr_formatted(unsigned long long ptr, int width, int left_align)
{
	char	*ptr_str;
	int		result;
	int		ptr_len;

	if (ptr == 0)
	{
		ptr_str = "(nil)";
		return (apply_width(ptr_str, width, left_align));
	}
	ptr_len = ft_len_ptr(ptr) + 2;
	ptr_str = malloc(ptr_len + 1);
	if (!ptr_str)
		return (0);
	ptr_str[0] = '0';
	ptr_str[1] = 'x';
	ft_put_ptr_to_string(ptr, ptr_str + 2);
	ptr_str[ptr_len] = '\0';
	result = apply_width(ptr_str, width, left_align);
	free(ptr_str);
	return (result);
}
