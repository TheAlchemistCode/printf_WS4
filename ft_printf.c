/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:37:37 by clyon             #+#    #+#             */
/*   Updated: 2025/09/01 16:25:01 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 
 * 𝐟𝐭_𝐩𝐫𝐢𝐧𝐭𝐟 - 𝐶𝑢𝑠𝑡𝑜𝑚 𝑖𝑚𝑝𝑙𝑒𝑚𝑒𝑛𝑡𝑎𝑡𝑖𝑜𝑛 𝑜𝑓 𝑝𝑟𝑖𝑛𝑡𝑓 𝑓𝑢𝑛𝑐𝑡𝑖𝑜𝑛
 * 
 * 𝐅𝐨𝐫𝐦𝐚𝐭: %[𝑓𝑙𝑎𝑔𝑠][𝑤𝑖𝑑𝑡ℎ].[𝑝𝑟𝑒𝑐𝑖𝑠𝑖𝑜𝑛][𝑠𝑝𝑒𝑐𝑖𝑓𝑖𝑒𝑟]
 * 
 * 𝐇𝐨𝐰 𝐯𝐚𝐫𝐢𝐚𝐝𝐢𝐜 𝐚𝐫𝐠𝐮𝐦𝐞𝐧𝐭𝐬 𝐰𝐨𝐫𝐤:
 * 𝟷. 𝑣𝑎_𝑠𝑡𝑎𝑟𝑡(𝑎𝑟𝑔𝑠, 𝑠𝑡𝑟) - "𝑃𝑜𝑖𝑛𝑡 𝑐𝑢𝑟𝑠𝑜𝑟 𝑡𝑜 𝑓𝑖𝑟𝑠𝑡 𝑎𝑟𝑔𝑢𝑚𝑒𝑛𝑡 𝑎𝑓𝑡𝑒𝑟 𝑠𝑡𝑟"
 * 𝟸. 𝑣𝑎_𝑎𝑟𝑔(𝑎𝑟𝑔𝑠, 𝑡𝑦𝑝𝑒) - "𝐺𝑒𝑡 𝑐𝑢𝑟𝑟𝑒𝑛𝑡 𝑎𝑟𝑔𝑢𝑚𝑒𝑛𝑡 𝑎𝑠 𝑡𝑦𝑝𝑒, 𝑚𝑜𝑣𝑒 𝑡𝑜 𝑛𝑒𝑥𝑡"
 * 𝟹. 𝑣𝑎_𝑒𝑛𝑑(𝑎𝑟𝑔𝑠)       - "𝐶𝑙𝑒𝑎𝑛 𝑢𝑝 𝑤ℎ𝑒𝑛 𝑑𝑜𝑛𝑒"
 * 
 * 𝑐 = 𝑐ℎ𝑎𝑟𝑎𝑐𝑡𝑒𝑟 (𝑎𝑠𝑐𝑖𝑖)
 * 𝑠 = 𝑠𝑡𝑟𝑖𝑛𝑔
 * 𝑝 = 𝑝𝑜𝑖𝑛𝑡𝑒𝑟 (𝑎𝑑𝑑𝑟𝑒𝑠𝑠 𝑖𝑛 𝑚𝑒𝑚𝑜𝑟𝑦)
 * 𝑑 = 𝑑𝑒𝑐𝑖𝑚𝑎𝑙
 * 𝑢 = 𝑢𝑛𝑠𝑖𝑔𝑛𝑒𝑑 𝑑𝑒𝑐𝑖𝑚𝑎𝑙
 * 𝑥 = ℎ𝑒𝑥𝑎𝑑𝑒𝑐𝑖𝑚𝑎𝑙 (𝑙𝑜𝑤𝑒𝑟𝑐𝑎𝑠𝑒)
 * 
*/

int	ft_format(va_list args, const char format)
{
	if (format == 'c')
		return (ft_print_chr(va_arg(args, int)));
	else if (format == 's')
		return (ft_print_str(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_print_ptr(va_arg(args, unsigned long long)));
	else if (format == 'd' || format == 'i')
		return (ft_print_num(va_arg(args, int)));
	else if (format == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	else if (format == 'x' || format == 'X')
		return (ft_print_hex(va_arg(args, unsigned int), format));
	else if (format == '%')
		return (ft_print_chr('%'));
	return (0);
}

/* 𝑁𝐸𝑊: 𝐻𝑎𝑛𝑑𝑙𝑒 𝑓𝑜𝑟𝑚𝑎𝑡 𝑠𝑝𝑒𝑐𝑖𝑓𝑖𝑒𝑟 𝑤𝑖𝑡ℎ 𝑤𝑖𝑑𝑡ℎ 𝑎𝑛𝑑 𝑎𝑙𝑖𝑔𝑛𝑚𝑒𝑛𝑡 - 
 * 𝑝𝑟𝑜𝑐𝑒𝑠𝑠𝑒𝑠 𝑝𝑎𝑟𝑠𝑒𝑑 𝑤𝑖𝑑𝑡ℎ/𝑓𝑙𝑎𝑔𝑠 𝑓𝑜𝑟 𝑎𝑙𝑙 𝑓𝑜𝑟𝑚𝑎𝑡 𝑡𝑦𝑝𝑒𝑠
*/
int	ft_format_with_info(va_list args, t_format_info info)
{
	if (info.specifier == '%')
		return (ft_print_chr('%'));
	else if (info.specifier == 'c')
		return (apply_char_width(va_arg(args, int),
				info.width, info.left_align));
	else if (info.specifier == 's')
		return (handle_string_format_info(args, info));
	else if (info.specifier == 'd' || info.specifier == 'i')
		return (handle_integer_format_info(args, info));
	else if (info.specifier == 'u')
		return (ft_print_unsigned_formatted_info(args, info));
	else if (info.specifier == 'x' || info.specifier == 'X')
		return (ft_print_hex_formatted_info(args, info));
	else if (info.specifier == 'p')
		return (ft_print_ptr_formatted_info(args, info));
	return (ft_format(args, info.specifier));
}

/* Helper function to process format specifiers */
static int	process_format(va_list args, t_format_info info)
{
	if (info.width > 0 || info.left_align
		|| info.precision >= 0 || info.zero_pad)
		return (ft_format_with_info(args, info));
	return (ft_format(args, info.specifier));
}

/* principle function */
int	ft_printf(const char *str, ...)
{
	int				i;
	va_list			args;
	int				length;
	t_format_info	info;

	i = 0;
	length = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			parse_format_info(str, &i, &info);
			length += process_format(args, info);
			i++;
		}
		else
		{
			length += ft_print_chr(str[i]);
			i++;
		}
	}
	va_end(args);
	return (length);
}
