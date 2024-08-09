/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inkahar <inkahar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:02:33 by inkahar           #+#    #+#             */
/*   Updated: 2024/08/01 11:37:12 by inkahar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		ft_puterr("error with malloc");
	return (ret);
}

bool	safe_mutex(t_mtx *mutex, t_opcode opceode)
{
	if (LOCK == opceode)
	{
		if (pthread_mutex_lock(mutex))
			return (false);
	}
	else if (UNLOCK == opceode)
	{
		if (pthread_mutex_unlock(mutex))
			return (false);
	}
	else if (INIT == opceode)
	{
		if (pthread_mutex_init(mutex, NULL))
			return (false);
	}
	else if (DESTROY == opceode)
	{
		if (pthread_mutex_destroy(mutex))
			return (false);
	}
	else
		return (false);
	return (true);
}

bool	safe_thread(pthread_t *thread, void *(*foo)(void *), void *data,
		t_opcode code)
{
	if (CREATE == code)
	{
		if (pthread_create(thread, NULL, foo, data))
			return (false);
	}
	else if (JOIN == code)
	{
		if (pthread_join(*thread, NULL), code)
			return (false);
	}
	else if (DETACH == code)
	{
		if (pthread_detach(*thread), code)
			return (false);
	}
	else
		return (false);
	return (true);
}
