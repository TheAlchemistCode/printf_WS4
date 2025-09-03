/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 00:00:00 by clyon             #+#    #+#             */
/*   Updated: 2025/09/02 00:00:00 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* NEW: Handle zero-padding for negative numbers (sign first, then zeros)
 * Fixes cases like %07d with -54 should be -000054 not 0000-54 */
int	handle_negative_zero_pad(char *content, int padding)
{
	int	total;

	total = ft_print_chr('-');
	total += print_zeros(padding);
	total += ft_print_str(content + 1);
	return (total);
}

/* NEW: Helper to create hex string for formatting
 * Split from ft_print_hex.c for norminette compliance (max 5 functions per file) */
char	*create_hex_string(unsigned int num, const char format)
{
	char	*hex_str;
	int		hex_len;

	if (num == 0)
		hex_len = 1;
	else
		hex_len = ft_hex_len(num);
	hex_str = malloc(hex_len + 1);
	if (!hex_str)
		return (NULL);
	if (num == 0)
	{
		hex_str[0] = '0';
		hex_str[1] = '\0';
	}
	else
	{
		ft_put_hex_to_string(num, format, hex_str);
		hex_str[hex_len] = '\0';
	}
	return (hex_str);
}

/* UPDATE_5: Helper to parse flags from format string - split from parse_format for norminette compliance */
void	parse_flags(const char *str, int *i, int *left_align, int *zero_pad)
{
	while (str[*i] == '-' || str[*i] == '0' || str[*i] == '+' || 
		   str[*i] == ' ' || str[*i] == '#')
	{
		if (str[*i] == '-')
			*left_align = 1;
		if (str[*i] == '0')
			*zero_pad = 1;
		(*i)++;
	}
}
