/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:38:00 by clyon             #+#    #+#             */
/*   Updated: 2025/09/01 16:43:36 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * ft_uitoa:
 * Converts an unsigned int 'n' into a string representation (base 10).
 * Returns a pointer to a malloc'd string containing the number as characters.
 * Caller is responsible for freeing the allocated memory.
 * 
 *  this pointer, *num, is used to hold the string result (ascii)
 *  len is the number of characters needed to print the string
 *  in the loop,  %10 is to get the digit at the end (right side)
 *  +48 converts to ascii,
 *  n / 10 is to remove the last digit, len -- to move left in the string
 * UPDATE_8: Fixed to handle n == 0 case properly
 */
char	*ft_uitoa(unsigned int n)
{
	char	*num;
	int		len;

	len = ft_num_len(n);
	num = (char *)malloc((len + 1) * sizeof(char));
	if (!num)
		return (NULL);
	num[len] = '\0';
	if (n == 0)
	{
		num[0] = '0';
		return (num);
	}
	while (n != 0)
	{
		num[len - 1] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (num);
}

/*This function calculates how many digits are in an unsigned integer*/
int	ft_num_len(unsigned int num)
{
	int	len;

	if (num == 0)
		return (1);
	len = 0;
	while (num != 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

/*
 * ft_print_unsigned:
 * Prints an unsigned integer 'n' to standard output (fd = 1).
 * Uses ft_uitoa to convert the number to a string, then prints it.
 * Returns the number of characters written.
 */
int	ft_print_unsigned(unsigned int n)
{
	int		length;
	char	*num;

	length = 0;
	if (n == 0)
		length += write(1, "0", 1);
	else
	{
		num = ft_uitoa(n);
		length += ft_print_str(num);
		free(num);
	}
	return (length);
}

/* UPDATE: Enhanced version with struct - REFACTORED to use ≤4 parameters!
 * Handles format specifiers like %5u, %-10u, %.5u, %05u
 * UPDATE_9: Fixed memory leak in else branch */
int	ft_print_unsigned_formatted(unsigned int n, t_format_info info)
{
	char	*num;
	char	*processed;
	int		result;

	if (should_hide_zero(n, info.precision))
		return (apply_width("", info.width, info.left_align));
	num = ft_uitoa(n);
	if (info.precision >= 0)
	{
		processed = apply_number_precision(num, info.precision, 0);
		result = apply_width(processed, info.width, info.left_align);
		free(num);
		if (processed != num)
			free(processed);
	}
	else
	{
		result = apply_width_with_zeros(num, info.width, info.left_align, info.zero_pad);
		free(num);
	}
	return (result);
}
