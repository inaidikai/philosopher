/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:02:06 by inkahar           #+#    #+#             */
/*   Updated: 2024/08/01 11:36:48 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	philo_number;

	philo_number = philo->table->philo_number;
	philo->two_fork = &forks[position];
	philo->one_fork = &forks[(position + 1) % philo_number];
	if (philo->id % 2 == 0)
	{
		philo->one_fork = &forks[position];
		philo->two_fork = &forks[(position + 1) % philo_number];
	}
}

static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philo_number)
	{
		philo = table->philo + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_c = 0;
		philo->table = table;
		safe_mutex(&philo->philo_mutex, INIT);
		assign_forks(philo, table->forks, i);
	}
}

void	dataq_inti(t_table *table)
{
	int	i;

	i = -1;
	table->end_sim = false;
	table->all_threads_ready_syn = false;
	table->threads_run_nbr = 0;
	table->philo = safe(sizeof(t_philo) * table->philo_number);
	table->forks = safe(sizeof(t_fork) * table->philo_number);
	safe_mutex(&table->table_mutex, INIT);
	safe_mutex(&table->write_mutex, INIT);
	while (++i < table->philo_number)
	{
		safe_mutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
}
