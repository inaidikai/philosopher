/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:02:26 by inkahar           #+#    #+#             */
/*   Updated: 2024/08/08 13:14:51 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static inline bool	ispace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

bool	valid_input(const char *str)
{
	int	len;

	len = 0;
	while (ispace(*str))
		str++;
	if (*str == '+')
		++str;
	if (*str == '-')
		return (ft_puterr("Error: Please, provide only positive numbers"));
	if (!is_digit(*str))
		return (ft_puterr("Error: Input should contain only digits"));
	while (is_digit(*str))
	{
		len++;
		str++;
	}
	if (len > 10)
		return (ft_puterr("Error: Number is too large"));
	return (true);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	if (!valid_input(str))
		return (-1);
	while (*str)
	{
		if (is_digit(*str))
			num = (num * 10) + (*str++ - '0');
		else
			return (ft_puterr("Error: No Number found"), -1);
	}
	if (num > INT_MAX)
		return (ft_puterr("Error: Number too large"), -1);
	return (num);
}

bool	parse(t_table *table, char **av)
{
	table->philo_number = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (table->philo_number == -1 || table->time_to_die == -1 || \
		table->time_to_eat == -1 || table->time_to_sleep == -1)
	{
		return (ft_puterr("Error"));
	}
	if (table->time_to_die < 6e4 || table->time_to_eat < 6e4
		|| table->time_to_sleep < 6e4 || table->philo_number > 200)
		return (ft_puterr("Error:time stamps> 60ms or philonbr <= 200"));
	if (av[5])
	{
		table->limit_meals = ft_atol(av[5]);
		if (table->limit_meals == -1)
			return (false);
	}
	else
		table->limit_meals = -1;
	return (true);
}
