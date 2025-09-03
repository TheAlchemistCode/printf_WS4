/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:38:59 by clyon             #+#    #+#             */
/*   Updated: 2025/09/01 17:14:13 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*Here we use recursion, to see how many sixteens go into our numb
* number, hex is built by dividing continusly with 16. 
* hex is built on 'remainders' of dividing by 16, from right to left
* len is acting as counter for each "16",
* to see how many characters will be printed
*/

int	ft_hex_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

/* used to display the hex number to the screen*/
void	ft_put_hex(unsigned int num, const char format)
{
	if (num >= 16)
	{
		ft_put_hex(num / 16, format);
		ft_put_hex(num % 16, format);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + 48), 1);
		else
		{
			if (format == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			else if (format == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

/* UPDATE: Helper to convert hex to string instead of direct output
 * Used by the formatted version for string manipulation */
void	ft_put_hex_to_string(unsigned int num, const char format, char *str)
{
	int	len;
	int	temp;

	len = ft_hex_len(num);
	str[len] = '\0';
	while (len > 0)
	{
		temp = num % 16;
		len--;
		if (temp <= 9)
			str[len] = temp + '0';
		else
		{
			if (format == 'x')
				str[len] = temp - 10 + 'a';
			else if (format == 'X')
				str[len] = temp - 10 + 'A';
		}
		num /= 16;
	}
}

int	ft_print_hex(unsigned int num, const char format)
{
	if (num == 0)
		return (write(1, "0", 1));
	else
		ft_put_hex(num, format);
	return (ft_hex_len(num));
}

/* UPDATE: Enhanced version with struct - REFACTORED to use ≤4 parameters!
 * UPDATE_2: Simplified and split for norminette compliance */
int	ft_print_hex_formatted(unsigned int num, t_format_info info)
{
	char	*hex_str;
	char	*processed;
	int		result;

	if (should_hide_zero(num, info.precision))
		return (apply_width("", info.width, info.left_align));
	hex_str = create_hex_string(num, info.specifier);
	if (!hex_str)
		return (0);
	if (info.precision >= 0)
	{
		processed = apply_no_prec(hex_str, info.precision, 0);
		result = apply_width(processed, info.width, info.left_align);
		if (processed != hex_str)
			free(processed);
	}
	else
		result = zero_space_padr(hex_str, info.width,
				info.left_align, info.zero_pad);
	free(hex_str);
	return (result);
}
