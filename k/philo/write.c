/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:02:57 by inkahar           #+#    #+#             */
/*   Updated: 2024/08/01 14:38:03 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	write_debug(t_philo_status status, t_philo *philo, long elas)
{
	if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
		&& (!simul_finished(philo->table)))
		printf(W " %-6ld " RE " %d has taken a fork\n", elas, philo->id);
	else if (EATING == status && !simul_finished(philo->table))
		printf(W "%-6ld " RE " %d is eating\n", elas, philo->id);
	else if (SLEEPING == status && !simul_finished(philo->table))
		printf(W "%-6ld" RE " %d is sleeping\n", elas, philo->id);
	else if (THINKING == status && !simul_finished(philo->table))
		printf(W "%-6ld" RE " %d is thinking\n", elas, philo->id);
	else if (DIED == status)
		printf(RED "%-6ld" RE " %d is died\n", elas, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elas;

	elas = gettime(MILLISECOND) - philo->table->start_sim;
	if (philo->full)
		return ;
	safe_mutex(&philo->table->write_mutex, LOCK);
	if (debug)
		write_debug(status, philo, elas);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& (!simul_finished(philo->table)))
			printf(CYAN "%-6ld %d has taken a fork\n"RE, elas, philo->id);
		else if (EATING == status && !simul_finished(philo->table))
			printf(GREEN "%-6ld %d is eating\n"RE, elas, philo->id);
		else if (SLEEPING == status && !simul_finished(philo->table))
			printf(YELLOW "%-6ld %d is sleeping\n"RE, elas, philo->id);
		else if (THINKING == status && !simul_finished(philo->table))
			printf(BLUE "%-6ld %d is thinking\n"RE, elas, philo->id);
		else if (DIED == status)
			printf(RED "%-6ld %d is died\n"RE, elas, philo->id);
	}
	safe_mutex(&philo->table->write_mutex, UNLOCK);
}
