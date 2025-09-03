/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:38:00 by clyon             #+#    #+#             */
/*   Updated: 2025/09/03 21:30:53 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 * 𝐟𝐭_𝐮𝐢𝐭𝐨𝐚:
 * 𝐂𝐨𝐧𝐯𝐞𝐫𝐭𝐬 𝐚𝐧 𝐮𝐧𝐬𝐢𝐠𝐧𝐞𝐝 𝐢𝐧𝐭 '𝐧' 𝐢𝐧𝐭𝐨 𝐚 𝐬𝐭𝐫𝐢𝐧𝐠 𝐫𝐞𝐩𝐫𝐞𝐬𝐞𝐧𝐭𝐚𝐭𝐢𝐨𝐧 (𝐛𝐚𝐬𝐞 𝟏𝟎).
 * 𝐑𝐞𝐭𝐮𝐫𝐧𝐬 𝐚 𝐩𝐨𝐢𝐧𝐭𝐞𝐫 𝐭𝐨 𝐚 𝐦𝐚𝐥𝐥𝐨𝐜'𝐝 𝐬𝐭𝐫𝐢𝐧𝐠 𝐜𝐨𝐧𝐭𝐚𝐢𝐧𝐢𝐧𝐠 𝐭𝐡𝐞 𝐧𝐮𝐦𝐛𝐞𝐫 𝐚𝐬 𝐜𝐡𝐚𝐫𝐚𝐜𝐭𝐞𝐫𝐬.
 * 𝐂𝐚𝐥𝐥𝐞𝐫 𝐢𝐬 𝐫𝐞𝐬𝐩𝐨𝐧𝐬𝐢𝐛𝐥𝐞 𝐟𝐨𝐫 𝐟𝐫𝐞𝐞𝐢𝐧𝐠 𝐭𝐡𝐞 𝐚𝐥𝐥𝐨𝐜𝐚𝐭𝐞𝐝 𝐦𝐞𝐦𝐨𝐫𝐲.
 * 
 *  𝐭𝐡𝐢𝐬 𝐩𝐨𝐢𝐧𝐭𝐞𝐫, *𝐧𝐮𝐦, 𝐢𝐬 𝐮𝐬𝐞𝐝 𝐭𝐨 𝐡𝐨𝐥𝐝 𝐭𝐡𝐞 𝐬𝐭𝐫𝐢𝐧𝐠 𝐫𝐞𝐬𝐮𝐥𝐭 (𝐚𝐬𝐜𝐢𝐢)
 *  𝐥𝐞𝐧 𝐢𝐬 𝐭𝐡𝐞 𝐧𝐮𝐦𝐛𝐞𝐫 𝐨𝐟 𝐜𝐡𝐚𝐫𝐚𝐜𝐭𝐞𝐫𝐬 𝐧𝐞𝐞𝐝𝐞𝐝 𝐭𝐨 𝐩𝐫𝐢𝐧𝐭 𝐭𝐡𝐞 𝐬𝐭𝐫𝐢𝐧𝐠
 *  𝐢𝐧 𝐭𝐡𝐞 𝐥𝐨𝐨𝐩,  %𝟏𝟎 𝐢𝐬 𝐭𝐨 𝐠𝐞𝐭 𝐭𝐡𝐞 𝐝𝐢𝐠𝐢𝐭 𝐚𝐭 𝐭𝐡𝐞 𝐞𝐧𝐝 (𝐫𝐢𝐠𝐡𝐭 𝐬𝐢𝐝𝐞)
 *  +𝟒𝟖 𝐜𝐨𝐧𝐯𝐞𝐫𝐭𝐬 𝐭𝐨 𝐚𝐬𝐜𝐢𝐢,
 *  𝐧 / 𝟏𝟎 𝐢𝐬 𝐭𝐨 𝐫𝐞𝐦𝐨𝐯𝐞 𝐭𝐡𝐞 𝐥𝐚𝐬𝐭 𝐝𝐢𝐠𝐢𝐭, 𝐥𝐞𝐧 -- 𝐭𝐨 𝐦𝐨𝐯𝐞 𝐥𝐞𝐟𝐭 𝐢𝐧 𝐭𝐡𝐞 𝐬𝐭𝐫𝐢𝐧𝐠
 * 𝐔𝐏𝐃𝐀𝐓𝐄_𝟖: 𝐅𝐢𝐱𝐞𝐝 𝐭𝐨 𝐡𝐚𝐧𝐝𝐥𝐞 𝐧 == 𝟎 𝐜𝐚𝐬𝐞 𝐩𝐫𝐨𝐩𝐞𝐫𝐥𝐲
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
int	ft_print_unsigned_formatted(unsigned int n, t_format_spec spec)
{
	char	*num;
	char	*processed;
	int		result;

	if (should_hide_zero(n, spec.precision))
		return (apply_width("", spec.width, spec.left_align));
	num = ft_uitoa(n);
	if (spec.precision >= 0)
	{
		processed = apply_no_prec(num, spec.precision, 0);
		result = apply_width(processed, spec.width, spec.left_align);
		free(num);
		if (processed != num)
			free(processed);
	}
	else
	{
		result = zero_space_padr(num, spec.width,
				spec.left_align, spec.zero_pad);
		free(num);
	}
	return (result);
}
