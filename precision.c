/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 00:00:00 by clyon             #+#    #+#             */
/*   Updated: 2025/09/02 00:00:00 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* NEW: Apply string precision - truncate string to precision length
 * Handles cases like %.3s which should only show first 3 characters
 * UPDATE: Enhanced NULL handling for cases like %.03s with NULL */
char	*apply_string_precision(char *str, int precision)
{
	char	*result;
	int		i;

	if (precision < 0 || !str)
		return (str);
	if (precision == 0)
		return ("");
	result = malloc(precision + 1);
	if (!result)
		return (str);
	i = 0;
	while (i < precision && str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

/* Helper function to build precision result string */
char	*build_precision_result(char *num, int precision, int is_negative, int zeros_needed)
{
	char	*result;
	int		i;
	int		j;
	int		extra_space;

	extra_space = 0;
	if (is_negative)
		extra_space = 1;
	result = malloc(precision + 1 + extra_space);
	if (!result)
		return (num);
	i = 0;
	if (is_negative)
		result[i++] = '-';
	while (zeros_needed-- > 0)
		result[i++] = '0';
	j = 0;
	if (is_negative)
		j = 1;
	while (num[j])
		result[i++] = num[j++];
	result[i] = '\0';
	return (result);
}

/* NEW: Apply number precision - pad with leading zeros
 * Handles cases like %.5d which should pad numbers with zeros to 5 digits
 * UPDATE: Removed ternary operators for norminette compliance
 * UPDATE_13: Split into helper functions for norminette 25-line compliance */
char	*apply_number_precision(char *num, int precision, int is_negative)
{
	int		num_len;
	int		zeros_needed;

	if (precision <= 0 || !num)
		return (num);
	num_len = ft_strlen(num);
	if (is_negative)
		num_len--;
	if (num_len >= precision)
		return (num);
	zeros_needed = precision - num_len;
	return (build_precision_result(num, precision, is_negative, zeros_needed));
}
