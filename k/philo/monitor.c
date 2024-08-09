/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:02:20 by inkahar           #+#    #+#             */
/*   Updated: 2024/08/01 15:54:37 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	elasped;
	long	ttd;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elasped = gettime(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal);
	ttd = philo->table->time_to_die / 1e3;
	if (elasped >= ttd)
		return (true);
	return (false);
}

void	*monitor_dine(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threads_runnig(&table->table_mutex, &table->threads_run_nbr,
			table->philo_number))
		;
	while (!simul_finished(table))
	{
		i = -1;
		while (++i < table->philo_number && !simul_finished(table))
		{
			if (philo_died(table->philo + i))
			{
				set_bool(&table->table_mutex, &table->end_sim, true);
				write_status(DIED, table->philo + i, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}
