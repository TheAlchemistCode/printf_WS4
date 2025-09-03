/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyon <clyon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:33:13 by clyon             #+#    #+#             */
/*   Updated: 2025/09/01 16:38:31 by clyon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_itoa - Integer to ASCII conversion
** 
** Converts an integer to its string representation by:
** 1. Counting required digits (including space for minus sign)
** 2. Allocating memory for the string
** 3. Filling digits from right to left using modulo and division
** 4. Using sign multiplier (-1 for negative) to handle negative numbers
**    without overflow issues (works correctly for INT_MIN)
**
** Example: -123 becomes "-123" by extracting digits 3,2,1 and placing
** them in reverse order after setting the minus sign at position 0.
*/

static size_t	num_digits(int n)
{
	size_t	counter;

	counter = 0;
	if (n <= 0)
		counter++;
	while (n != 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	counter;
	int		s;

	counter = num_digits(n);
	str = malloc(sizeof(char) * (counter + 1));
	if (str == NULL)
		return (NULL);
	s = 1;
	str[counter] = '\0';
	counter--;
	if (n < 0)
	{
		str[0] = '-';
		s = -1;
	}
	else if (n == 0)
		str[counter] = '0';
	while (n != 0)
	{
		str[counter] = ((n % 10) * s) + 48;
		n = n / 10;
		counter--;
	}
	return (str);
}

/* 
#include <stdio.h>
int		main(void)
{
	int number1 = 123456789;
	int number2 = 1;
	int number3 = 0;
	int number4 = 0001342;
	int number5 = 42;
	int number6 = 422;

	int number7 = -123456789;
	int number8 = -1;
	int number9 = -0;
	int number10 = -00101;
	int number11 = -42;
	int number12 = -422;

	ft_itoa(number1);
	printf("%s\n", ft_itoa(number2));
	printf("%s\n", ft_itoa(number3));
	ft_itoa(number4);
	printf("%s\n", ft_itoa(number5));
	ft_itoa(number6);
	ft_itoa(number7);
	ft_itoa(number8);
	ft_itoa(number9);
	ft_itoa(number10);
	ft_itoa(number11);
	ft_itoa(number12);

	return (0);
} */