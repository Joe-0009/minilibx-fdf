/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrachidi <yrachidi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:34:00 by yrachidi          #+#    #+#             */
/*   Updated: 2025/01/13 12:34:01 by yrachidi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	get_index(char c, int base)
{
	char	*small_h;
	char	*big_h;
	int		i;

	small_h = "0123456789abcdef";
	big_h = "0123456789ABCDEF";
	i = 0;
	while (i < base)
	{
		if (c == small_h[i] || c == big_h[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, int base)
{
	int	sign;
	int	i;
	int	result;

	i = 0;
	result = 0;
	sign = 1;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (get_index(str[i], base) != -1)
	{
		result = result * base + get_index(str[i], base);
		if (result < 0)
			return ((sign != -1) * -1);
		i++;
	}
	return (result * sign);
}
