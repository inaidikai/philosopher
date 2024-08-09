/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:02:12 by inkahar           #+#    #+#             */
/*   Updated: 2024/08/08 12:56:12 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (5 == argc || 6 == argc)
	{
		if (parse(&table, argv))
		{
			dataq_inti(&table);
			start(&table);
			clean(&table);
		}
	}
	else
	{
		return (printf("%s", "wrong input:\n"), 0);
	}
}
