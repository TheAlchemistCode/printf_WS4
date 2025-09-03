/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:37:37 by clyon             #+#    #+#             */
/*   Updated: 2025/09/01 16:25:01 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdint.h>

/* ========================================================================== */
/*                       𝑭𝑶𝑹𝑴𝑨𝑻 𝑰𝑵𝑭𝑶 𝑺𝑻𝑹𝑼𝑪𝑻𝑼𝑹𝑬                             */
/* ========================================================================== */

typedef struct s_format_info
{
	int		width;
	int		left_align;
	int		precision;
	int		zero_pad;
	char	specifier;
}	t_format_info;

/* ========================================================================== */
/*                            𝑴𝑨𝑰𝑵 𝑷𝑹𝑰𝑵𝑻𝑭 𝑭𝑼𝑵𝑪𝑻𝑰𝑶𝑵                        */
/* ========================================================================== */

int		ft_printf(const char *str, ...);

/* ========================================================================== */
/*                         𝑭𝑶𝑹𝑴𝑨𝑻 𝑷𝑨𝑹𝑺𝑰𝑵𝑮 & 𝑪𝑶𝑵𝑻𝑹𝑶𝑳                      */
/* ========================================================================== */

/* New format info functions - REDUCED parameters! */
void	init_format_info(t_format_info *info);
void	parse_flags_info(const char *str, int *i, t_format_info *info);
void	parse_width_info(const char *str, int *i, t_format_info *info);
void	parse_precision_info(const char *str, int *i, t_format_info *info);
char	parse_format_info(const char *str, int *i, t_format_info *info);

/* Updated functions - Now using t_format_info struct */
char	parse_format(const char *str, int *i, t_format_info *info);
void	parse_flags(const char *str, int *i, int *left_align, int *zero_pad);
int		ft_format(va_list args, const char format);
int		ft_format_with_info(va_list args, t_format_info info);

/* New struct-based format handlers*/
int		handle_string_format_info(va_list args, t_format_info info);
int		handle_integer_format_info(va_list args, t_format_info info);
int		ft_print_unsigned_formatted_info(va_list args, t_format_info info);
int		ft_print_hex_formatted_info(va_list args, t_format_info info);
int		ft_print_ptr_formatted_info(va_list args, t_format_info info);

/* ========================================================================== */
/*                         𝑾𝑰𝑫𝑻𝑯 & 𝑨𝑳𝑰𝑮𝑵𝑴𝑬𝑵𝑻 𝑯𝑬𝑳𝑷𝑬𝑹𝑺                     */
/* ========================================================================== */

int		apply_width(char *content, int width, int left_align);
int		apply_char_width(char c, int width, int left_align);
int		apply_width_with_zeros(char *content, int width,
			int left_align, int zero_pad);
int		print_spaces(int count);
int		print_zeros(int count);
int		print_left_aligned(char *content, int padding);
int		handle_negative_zero_pad(char *content, int padding);

/* ========================================================================== */
/*                         𝑷𝑹𝑬𝑪𝑰𝑺𝑰𝑶𝑵 𝑯𝑨𝑵𝑫𝑳𝑰𝑵𝑮                              */
/* ========================================================================== */

char	*apply_string_precision(char *str, int precision);
char	*apply_number_precision(char *num, int precision, int is_negative);
char	*build_precision_result(char *num, int precision,
			int is_negative, int zeros_needed);
int		should_hide_zero(int value, int precision);

/* ========================================================================== */
/*                       𝑭𝑶𝑹𝑴𝑨𝑻-𝑺𝑷𝑬𝑪𝑰𝑭𝑰𝑪 𝑯𝑨𝑵𝑫𝑳𝑬𝑹𝑺                         */
/* ========================================================================== */

/* REFACTORED FUNCTIONS - Now use t_format_info struct (≤4 parameters)! */
int		handle_string_format(va_list args, t_format_info info);
int		handle_integer_format(va_list args, t_format_info info);

/* ========================================================================== */
/*                         𝑩𝑨𝑺𝑰𝑪 𝑶𝑼𝑻𝑷𝑼𝑻 𝑭𝑼𝑵𝑪𝑻𝑰𝑶𝑵𝑺                         */
/* ========================================================================== */

int		ft_print_chr(int c);
int		ft_print_str(char *str);
void	ft_putstr(char *str);

/* ========================================================================== */
/*                         𝑩𝑨𝑺𝑰𝑪 𝑶𝑼𝑻𝑷𝑼𝑻 𝑭𝑼𝑵𝑪𝑻𝑰𝑶𝑵𝑺                         */
/* ========================================================================== */

int		ft_print_num(int n);
int		ft_print_unsigned(unsigned int n);
char	*ft_uitoa(unsigned int n);
int		ft_num_len(unsigned int num);

/* REFACTORED FUNCTION - Now uses t_format_info struct (≤4 parameters)! */
int		ft_print_unsigned_formatted(unsigned int n, t_format_info info);

/* ========================================================================== */
/*                         𝑯𝑬𝑿𝑨𝑫𝑬𝑪𝑰𝑴𝑨𝑳 𝑭𝑼𝑵𝑪𝑻𝑰𝑶𝑵𝑺                          */
/* ========================================================================== */

int		ft_print_hex(unsigned int num, const char format);
void	ft_put_hex(unsigned int num, const char format);
void	ft_put_hex_to_string(unsigned int num, const char format, char *str);
char	*create_hex_string(unsigned int num, const char format);
int		ft_hex_len(unsigned int num);

/* REFACTORED FUNCTION - Now uses t_format_info struct (≤4 parameters)! */
int		ft_print_hex_formatted(unsigned int num, t_format_info info);

/* ========================================================================== */
/*                         𝑷𝑶𝑰𝑵𝑻𝑬𝑹 𝑭𝑼𝑵𝑪𝑻𝑰𝑶𝑵𝑺                               */
/* ========================================================================== */

int		ft_print_ptr(unsigned long long ptr);
int		ft_print_ptr_formatted(unsigned long long ptr,
			int width, int left_align);
void	ft_put_ptr(uintptr_t ptr);
void	ft_put_ptr_to_string(uintptr_t ptr, char *str);
int		ft_len_ptr(uintptr_t num);

#endif
